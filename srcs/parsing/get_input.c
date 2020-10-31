/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:05:23 by obouykou          #+#    #+#             */
/*   Updated: 2020/06/08 14:05:23 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		print_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		printf("TAB[%d] = |%s|\n", i, tab[i]);
}


/* t_list		*ft_lstnew(void *content)
{
	t_list	*l;

	if (!(l = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	l->content = content;
	l->next = NULL;
	return (l);
}

int			cmd_len(char **tab, int i)
{
	t_cmd	n_cmd;

	i = -1;
	while (tab[++i])
	{
		
	}
}

void		test_input(t_ms *ms, char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
	{
		
	}
} */

void		parse_in(t_ms *ms)
{
	int n;
	
	n = read(0, ms->input, SIZE);
	ms->input[n - 1] = 0;
	//test_input(ms, ms->input);
	if ((ms->tab = ft_split_ig(ms->input, ' ', &ms->stx_err)) == NULL)
	{
		ft_putendl_fd("Error : splitting error !", 1);
		exit(1);
	}
	if (ms->stx_err)
	{
		ft_putstr_fd("minishell: syntax error", 1);
		return ;
	}
	print_tab(ms->tab);
	//test_input(ms, ms->tab);
}
