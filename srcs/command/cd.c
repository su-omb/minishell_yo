/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:04:48 by yslati            #+#    #+#             */
/*   Updated: 2020/11/29 11:14:49 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		set_oldpwd(t_ms *ms)
{
	ms->env = set_env("OLDPWD", ms->pwd, ms->env);
	ms->pwd = getcwd(NULL, 0);
	ms->env = set_env("PWD", ms->pwd, ms->env);
}

int			ft_cd(t_ms *ms)
{
	int i;
	int x;

	i = 0;
	x = 0;
	if (!ms->cmds->args[1] || !ft_strcmp(ms->cmds->args[1], "~"))
	{
		if ((i = get_env(ms->env, "HOME")) < 0)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		else
			chdir(ms->env[i] + 5);
	}
	else if (!ft_strcmp(ms->cmds->args[1], "-"))
	{
		if ((i = get_env(ms->env, "OLDPWD")) != -1)
			chdir(ms->env[i] + 7);
		else
			x = cmd_error(2, "cd", NULL);
	}
	else if (ms->cmds->args[1] != NULL)
		if (chdir(ms->cmds->args[1]) != 0)
			x = cmd_error(1, "cd", ms->cmds->args[1]);
	if (x == 0)
		set_oldpwd(ms);
	return (0);
}
