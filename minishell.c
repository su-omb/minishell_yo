/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 09:35:39 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/26 09:35:39 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void		check_command(t_ms *ms, char **env)
{
	if (env)
		ms->env = arrdup(env, arrlen(env));
	if (!ft_strcmp(ms->cmds->cmd, "cd"))
		ft_cd(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "pwd"))
		ft_pwd(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "env"))
		ft_env(ms, env);
	else if (!ft_strcmp(ms->cmds->cmd, "export"))
		ft_export(ms, env);
	else if (!ft_strcmp(ms->cmds->cmd, "unset"))
		ft_unset(ms, env);
	else
		puts("soon");
}

void		minishell(char **env, int step)
{
	t_ms ms;

	if (!step)
		init(&ms, 0);
	while (1)
	{
		init(&ms, 1);
		ft_putstr_fd("\033[1;31m$minishell$~> \033[0m",1);
		parse(&ms);
		if (ms.input[0] == '\0')
			continue ;
 		else if (!ft_strcmp(ms.cmds->cmd, "clear") || !ft_strcmp(ms.cmds->cmd, "cl"))
			ft_putstr_fd("\e[1;1H\e[2J",1);
		else
			check_command(&ms, env);
	}

}

int		main(int ac,char **av, char **env)
{
	ac = 0;
	av = NULL;
	minishell(env, 0);
	return(0);
}