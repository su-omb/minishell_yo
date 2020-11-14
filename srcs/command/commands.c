/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:56:00 by yslati            #+#    #+#             */
/*   Updated: 2020/11/14 11:42:06 by yslati           ###   ########.fr       */
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

void			exec_command(t_ms *ms)
{
	int		st = 0;

	while(ms->cmds)
	{
		if (!is_builtin_sys(ms->cmds->cmd) /* || cmd->next */)
		{
			pid_t		pid = fork();
			if (pid == 0)
			{
				if (execve(get_exec_path(ms), ms->cmds->args, ms->env) < 0)
					printf("%s", strerror(errno));
			}
			else
				waitpid(pid, &st, 0);
		}
		else
		{
			check_command(ms);
		}
		ms->cmds = ms->cmds->next;
	}
}

char 		*get_exec_path(t_ms *ms)
{
	int i;
	char **tab;
	char *path;
	struct stat stats;

	i = 0;
	tab  = ft_split(ms->env[i] + 5, ':');
	i = get_env(ms->env, "PATH");
	if (tab[i])
	{
		puts("here");
		while (tab[i])
		{
			path = ft_strjoin(tab[i], "/");
			path = ft_strjoin(path, ms->cmds->cmd);
			if ((stat(path, &stats)) == 0)
				if (stats.st_mode & X_OK)
					return (path);
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
