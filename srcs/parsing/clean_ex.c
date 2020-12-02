/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:23:08 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/02 12:07:54 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_stx_err(t_ms *ms)
{
	ft_putendl_fd("minishell: syntax error", 1);
	if (ms->cmd_tab)
		ms->cmd_tab = free_str_table(ms->cmd_tab);
}

void	clean(t_ms *ms)
{
	free(ms->input); // Attention : free the whole struct
}

void	errex(t_ms *ms, int step)
{
	if (ms->err == RDIN_ERR)
		ft_putendl_fd("minishell: reading input error", 1);
	else if (ms->err == SPLT_ERR)
		ft_putendl_fd("minishell: splitting input error", 1);
	if (!step)
		clean(ms); // needs more free functions
	exit(ms->err);
}
