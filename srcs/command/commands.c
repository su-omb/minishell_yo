/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:56:00 by yslati            #+#    #+#             */
/*   Updated: 2020/11/07 10:30:45 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		check_command(t_ms *ms, char **env)
{
	if (!ms->env)
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
	else if (!ft_strcmp(ms->cmds->cmd, "exit"))
		ft_exit(ms);
	else
		puts("soon");
}
