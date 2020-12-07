/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:04:48 by yslati            #+#    #+#             */
/*   Updated: 2020/12/05 20:27:53 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		set_oldpwd(t_ms *ms)
{
	ms->env = set_env(ft_strdup("OLDPWD"), ms->pwd, &ms->env, '\0');
	ms->p_env = set_env(ft_strdup("OLDPWD"), ms->pwd, &ms->p_env, 'p');
	ms->pwd = ft_free(ms->pwd);
	ms->pwd = getcwd(NULL, 0);
	ms->env = set_env(ft_strdup("PWD"), ms->pwd, &ms->env, '\0');
	ms->p_env = set_env(ft_strdup("PWD"), ms->pwd, &ms->p_env, 'p');
}

int			ft_cd(t_ms *ms)
{
	int i;
	int is;

	i = 0;
	is = 0;
	if (!ms->cmds->args[1] || !ft_strcmp(ms->cmds->args[1], "~"))
	{
		if ((i = get_env(ms->env, ft_strdup("HOME"))) < 0 && (is = 1))
			cmd_error(ms, HOME_NOT_SET_ERR, NULL, "cd");
		else
			chdir(ms->env[i] + 5);
	}
	else if (!ft_strcmp(ms->cmds->args[1], "-")
			|| !ft_strcmp(ms->cmds->args[1], "~-"))
	{
		if ((i = get_env(ms->env, ft_strdup("OLDPWD"))) != -1)
			chdir(ms->env[i] + 7);
		else
			is = cmd_error(ms, OLDPWD_ERR, "cd", NULL);
	}
	else if (ms->cmds->args[1] != NULL && *ms->cmds->args[1] != '\0')
		if (chdir(ms->cmds->args[1]) != 0)
			is = cmd_error(ms, F_NOT_FOUND_ERR, "cd", ms->cmds->args[1]);
	if (is == 0)
		set_oldpwd(ms);
	return (0);
}
