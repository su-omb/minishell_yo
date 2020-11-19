/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:56:00 by yslati            #+#    #+#             */
/*   Updated: 2020/11/19 14:55:47 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int 	is_builtin_sys(char *cmds)
{
	if (ft_strcmp(cmds, "env") && ft_strcmp(cmds, "cd") &&
		ft_strcmp(cmds, "pwd") && ft_strcmp(cmds, "export") &&
		ft_strcmp(cmds, "unset") && ft_strcmp(cmds, "echo") &&
		ft_strcmp(cmds, "exit"))	
		return 0;
	return (1);
}

/* void			do_command(t_ms *ms)
{
	
} */


void			open_file(t_cmd *tmp)
{
	int 	fd;

	while (tmp->redir && !tmp->end)
	{
		while (tmp->redir == TRUNC && !tmp->end)
		{
			fd = open(tmp->next->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			// puts("trunc");
			tmp = tmp->next;
		}
		while (tmp->redir == APPEND && !tmp->end)
		{
			fd = open(tmp->next->cmd, O_WRONLY | O_CREAT | O_APPEND, 0666);
			// puts("append");
			tmp = tmp->next;
		}
	}
	dup2(fd, 1);
}

void			read_file(t_cmd *tmp)
{
	int fd;

	fd = open(tmp->next->cmd, O_RDONLY);
	dup2(fd, 0);
}

void			save_fds(int *fds)
{
	fds[0] = dup(0);
	fds[1] = dup(1);
	fds[2] = dup(2);
}

void			restore_fds(int *fds)
{
	dup2(fds[0], 0);
	close(fds[0]);
	dup2(fds[1], 1);
	close(fds[1]);
	dup2(fds[2], 2);
	close(fds[2]);
}

void			ft_redir(t_cmd *tmp)
{
	
	if (tmp->redir == TRUNC)
		open_file(tmp);
	if (tmp->redir == APPEND)
		open_file(tmp);
	if (tmp->redir == READ)
		read_file(tmp);
}

pid_t			run_child(t_ms *ms, int *i)
{
	pid_t	pid;
	t_cmd	*tmp;
	
	tmp = ms->cmds;
	pid = fork();
	if (pid == 0)
	{

		if (ms->pp_count && ms->cmds->redir != TRUNC)
		{
			if (ms->j != 0)
			{
				if (dup2(ms->fds[ms->j - 2], 0) < 0)
				{
					perror("dup2");
					exit(0);
				}
			}
			if (ms->cmds->next && !ms->cmds->end)
			{
				if (dup2(ms->fds[ms->j + 1], 1) < 0)
				{
					perror("dup2");
					exit(0);
				}
			}
		}
		*i = 0;
		while (*i < 2 * ms->pp_count)
			close(ms->fds[++*i]);
		if (ms->cmds->redir)
			ft_redir(tmp);
		if (ms->cmds->cmd[0] == '/' || (ms->cmds->cmd[0] == '.' &&  ms->cmds->cmd[1] == '/'))
		{
			if (execve(ms->cmds->cmd, ms->cmds->args, ms->env) < 0)
			{
				ft_putstr_fd("minishell: ", 1);
				perror(ms->cmds->cmd);
				exit(0);
			}
		}
		else
			execve(get_exec_path(ms), ms->cmds->args, ms->env);
			/* printf("%s\n", strerror(errno)) */;
		exit(0);
	}
	return (pid);
}

void			exec_command(t_ms *ms)
{
	int		st = 0;
	pid_t	pid;
	int		i;
	
	i = 0;
	ms->fds = (int *)malloc((2 * ms->pp_count)*sizeof(int));
	if ((ms->cmd_err == 1 && !ms->cmds) || (ms->cmds && ms->cmds->is_err == STX_ERR))
		ft_putstr_fd("minishell: syntax error\n", 1);
	else
	{
		while (ms->cmds)
		{
			while (i < 2 * ms->pp_count && ms->pp_count)
			{
				pipe(ms->fds + i * 2);
				i++;
			}
			ms->j = 0;
			if ((ms->cmds->next && !ms->cmds->end) || (!is_builtin_sys(ms->cmds->cmd)))
			{
				while(ms->cmds)
				{
					save_fds(ms->backup);
					if ((ms->cmds->start == 0 && ms->cmds->prev->redir) || (ms->cmds->start && is_builtin_sys(ms->cmds->cmd) && !ms->cmds->redir))
						break ;
					pid = run_child(ms, &i);
					if (pid < 0)
					{
						perror("Fork error");
						exit(0);
					}
					if (ms->cmds->end)
						break ;
					else
						ms->cmds = ms->cmds->next;
					ms->j += 2;
				}
				i = 0;
				while (i < 2 * ms->pp_count && ms->pp_count)
					close(ms->fds[i++]);
				if (!ms->pp_count)
					waitpid(pid, &st, 0);
				else
				{
					i = -1;
					while (++i < ms->pp_count + 1)
						wait(&st);
				}
				restore_fds(ms->backup);
			}
			if (is_builtin_sys(ms->cmds->cmd))
				check_command(ms);
			ms->cmds = ms->cmds->next;
		}
	}
}

char 		*get_exec_path(t_ms *ms)
{
	int			i;
	char		**tab;
	char		*path;
	struct		stat stats;

	if ((i = get_env(ms->env, "PATH")) != -1)
	{
		tab  = ft_split(ms->env[i] + 5, ':');
		i = 0;
		while (tab[i])
		{
			path = ft_strjoin(tab[i], "/");
			path = ft_strjoin(path, ms->cmds->cmd);
			if ((stat(path, &stats)) == 0)
			{

				if (stats.st_mode & X_OK)
					return (path);
			}
			/* else if ((stat(path, &stats)) == -1)
			{
				//puts("not exec");
			} */
			i++;
		}
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(ms->cmds->cmd, 1);
		ft_putstr_fd(": command not found\n", 1);
	}
	else
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(ms->cmds->cmd, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
	//free(path);
	return (NULL);
}

void		check_command(t_ms *ms)
{
	
	if (!ft_strcmp(ms->cmds->cmd, "cd"))
		ft_cd(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "pwd"))
		ft_pwd(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "env"))
		ft_env(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "export"))
		ft_export(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "unset"))
		ft_unset(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "echo"))
		ft_echo(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "exit"))
		ft_exit(ms);
	// else
	// 	execve(get_exec_path(ms), ms->cmds->args, ms->env);
}
