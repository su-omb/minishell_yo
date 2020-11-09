/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:30:38 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/09 11:56:32 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		print_tab(char **tab, FILE *f)
{
	int i;

	i = -1;
//	fprintf(f, "\n**ARGS Tab length = |%d|\n", tb_len(tab));
	if (!tab)
		fputs("\nARGS TAB is NULL\n", f);
	if (tab)
		while (tab[++i])
			fprintf(f, "\tARG[%d] = |%s|", i, tab[i]);
}

t_cmd		*get_head(t_cmd *cmds)
{
	while (cmds && cmds->prev)
		cmds = cmds->prev;
	return (cmds);
}

void		print_cmds(t_cmd *cmds)
{
	FILE *f;
	f = fopen("debug", "w+");
	if (cmds == NULL)
		fputs("\nERROR: ==> cmds is NULL\n", f);
	while (cmds)
	{
		fprintf(f,"\n==> CMD=|%s|\n\nARGS:\n", cmds->cmd);
		print_tab(cmds->args, f);
		fprintf(f, "\nStart=|%d| End=|%d| Redir=|%c|%d|\n", 
					cmds->start, cmds->end, cmds->redir, cmds->redir);
		cmds = cmds->next;
	}
	fclose(f);
}
