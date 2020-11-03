/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:03:38 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/03 14:53:24 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			get_dir(t_ms *ms)
{
	if (ms->pwd[0] != 0)
	{
		//ft_strcpy(ms->old_pwd, ms->pwd);
		ft_bzero(ms->pwd, sizeof(ms->pwd));
	}
	if ((ms->pwd = getcwd(NULL, 0)) == NULL)
		ft_putendl_fd("PWD error", 1);
	else
	{
		ft_putendl_fd(ms->pwd, 1);
		ms->old_pwd = ms->pwd;
		return (1);
	}
	return (0);
}

