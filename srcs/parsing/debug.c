/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:30:38 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/03 20:03:37 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		print_tab(char **tab)
{
	int i;

	i = -1;
	//printf("\nTable length = |%d|\n", tb_len(tab));
	if (!tab)
		puts("\nARGS TAB is NULL\n");
	if (tab)
		while (tab[++i])
			printf("\tARG[%d] = |\033[1;31m%s\033[0m|", i, tab[i]);
}

t_cmd		*get_head(t_cmd *cmds)
{
	if (cmds == NULL)
	{
		puts("\nERROR: ==> cmds is NULL\n");
		return(NULL);
	}
	while (cmds && cmds->prev)
		cmds = cmds->prev;
	return (cmds);
}

void		print_cmds(t_cmd *cmds)
{
	cmds = get_head(cmds);
	while (cmds)
	{
		printf("\n==> CMD=|\033[1;32m%s\033[0m|\n\nARGS:\n", cmds->cmd);
		print_tab(cmds->args);
		printf("\nStart=|%d| End=|%d| Redir=|%c|\n", cmds->start, cmds->end, cmds->redir);
		cmds = cmds->next;
	}
}
