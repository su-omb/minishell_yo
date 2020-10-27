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

int		tb_len(char **table)
{
	int len;

	len = 0;
	if (table)
		while (table[len])
			++len;
	return (len);
}

char			**free_str_table(char **tab, int size)
{
	if (!tab)
		return (NULL);
	while (size--)
		free(tab[size]);
	free(tab);
	return (NULL);
}

void		print_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		printf("TAB[%d] = |%s|\n", i, tab[i]);
}

void		get_input(t_ms *ms)
{
	int n;
	
	n = read(0, ms->input, SIZE);
	ms->input[n - 1] = 0;
	if ((ms->tab = ft_split(ms->input, ' ')) == NULL)
	{
		ft_putendl_fd("Error : spliting error !", 1);
		exit(1);
	}
	//print_tab(ms->tab);
}
