/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:56:00 by yslati            #+#    #+#             */
/*   Updated: 2020/11/19 09:19:24 by yslati           ###   ########.fr       */
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

/* pid_t			run_child(t_ms *ms)
{
	pid_t	pid;
	
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

void			exec_command(t_ms *ms)
{
	int		st = 0;
	int		fds[2 * ms->pp_count];
	int		j;
	pid_t	pid;
	//int		fd;
	int		i;
	t_cmd	*tmp;
	
	tmp = ms->cmds;
	i = 0;
	if ((ms->cmd_err == 1 && !ms->cmds) || (ms->cmds && ms->cmds->is_err == STX_ERR))
		ft_putstr_fd("minishell: syntax error\n", 1);
	else
	{
		while (ms->cmds)
		{
			while (i < 2 * ms->pp_count && ms->pp_count)
			{
				pipe(fds + i * 2);
				i++;
			}
			j = 0;
			if ((ms->cmds->next && !ms->cmds->end) || (!is_builtin_sys(ms->cmds->cmd)))
			{
				while(ms->cmds)
				{
					if (ms->cmds->start == 0 && ms->cmds->prev->redir)
						break ;
					if (ms->cmds->start)
						if (is_builtin_sys(ms->cmds->cmd))
							break ;
					pid = fork();
					if (pid == 0)
					{
						if (ms->pp_count && ms->cmds->redir != TRUNC)
						{
							if (j != 0)
							{
								if (dup2(fds[j - 2], 0) < 0)
								{
									perror("dup2");
									exit(0);
								}
							}
							if (ms->cmds->next && !ms->cmds->end)
							{
								if (dup2(fds[j + 1], 1) < 0)
								{
									perror("dup2");
									exit(0);
								}
							}
						}
						i = 0;
						while (i < 2 * ms->pp_count)
						{
							close(fds[i++]);
						}
						if (ms->cmds->redir == TRUNC /* && ms->cmds->next->end *//*  && ms->skip != 1 */)
						{
							//ms->skip = 1;
							// puts("if trunc");
							open_file(tmp);
							//printf("cmd : |%s|\n", ms->cmds->cmd);
							//fd = open(ms->cmds->next->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
							//dup2(fd, 1);
						}
						if (ms->cmds->redir == APPEND/*  && ms->cmds->end */)
						{
							//ms->skip = 1;
							// puts("if append");
							open_file(tmp);
							//fd = open(ms->cmds->next->args[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
							//dup2(fd, 1);
						}
						/* if (ms->cmds->redir == READ)
						{
							fd = open(ms->cmds->next->args[0], O_RDONLY);
							dup2(fd, 0);
						} */
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
					else if (pid < 0)
					{
						perror("Fork error");
						exit(0);
					}
					if (ms->cmds->end)
						break ;
					else
						ms->cmds = ms->cmds->next;
					j += 2;
				}
				i = 0;
				while (i < 2 * ms->pp_count && ms->pp_count)
					close(fds[i++]);
				if (!ms->pp_count)
					waitpid(pid, &st, 0);
				else
				{
					i = -1;
					while (++i < ms->pp_count + 1)
						wait(&st);
				}
			}
			else
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
