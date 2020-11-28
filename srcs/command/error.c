/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:05:17 by yslati            #+#    #+#             */
/*   Updated: 2020/11/28 14:34:40 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			cmd_error(int err, char *cmd, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (err == 2)
		ft_putendl_fd("OLDPWD not set", 2);
	else if (err == 1)
	{
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	return (1);
}

int			ft_error(t_ms *ms, int err)
{
	ft_putstr_fd("minishell: ", 2);
	if (err == STX_ERR && (ms->ret_status = 258))
		ft_putstr_fd("syntax error", 2);
	else
	{	
		ft_putstr_fd(ms->cmds->cmd, 2);
		if (err == F_NOT_FOUND_ERR && (ms->ret_status = 1))
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (err == CMD_NOT_FOUND_ERR && (ms->ret_status = 127))
			ft_putstr_fd(": command not found\n", 2);
	}
	return (0);
}
