/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:05:17 by yslati            #+#    #+#             */
/*   Updated: 2020/11/25 14:51:43 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int			ft_error(t_ms *ms, int err)
{
	ft_putstr_fd("minishell: ", 1);
	if (err == STX_ERR && (ms->ret_status = 258))
		ft_putstr_fd("syntax error", 1);
	else
	{	
		ft_putstr_fd(ms->cmds->cmd, 1);
		if (err == F_NOT_FOUND_ERR && (ms->ret_status = 1))
			ft_putstr_fd(": No such file or directory\n", 1);
		else if (err == CMD_NOT_FOUND_ERR && (ms->ret_status = 127))
			ft_putstr_fd(": command not found\n", 1);
	}
	return (0);
}
