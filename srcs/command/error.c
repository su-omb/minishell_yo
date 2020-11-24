/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:05:17 by yslati            #+#    #+#             */
/*   Updated: 2020/11/23 13:26:58 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int			ft_error(t_ms *ms, int err)
{
	ft_putstr_fd("minishell: ", 1);
	if (err == STX_ERR)
	{
		ft_putstr_fd("syntax error", 1);
		ms->status = 258;
	}
	else
	{	
		ft_putstr_fd(ms->cmds->cmd, 1);
		if (err == 2)
		{
			ft_putstr_fd(": No such file or directory\n", 1);
			ms->status = 1;
		}
		else if (err == 4)
		{
			ft_putstr_fd(": command not found\n", 1);
			ms->status = 127;
		}
		//else if 

	}
	return (0);
}
