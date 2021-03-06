/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 20:52:31 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/07 12:30:49 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		get_line(t_ms *ms, int *i, int b, char **tmp)
{
	if ((*i = get_next_line(0, &ms->input)) < 0)
	{
		ms->err = RDIN_ERR;
		errex(ms, 0);
	}
	if (b == 2)
	{
		*tmp = clean_join(*tmp, ms->input);
		free(ms->input);
		ms->input = *tmp;
	}
}

void		get_input(t_ms *ms)
{
	int		i;
	int		b;
	int		len;
	char	*tmp;

	b = 1;
	while (b)
	{
		get_line(ms, &i, b, &tmp);
		if ((len = ft_strlen(ms->input)) && ms->input[len - 1] != '\n')
		{
			ft_putstr_fd("  \b\b", 1);
			tmp = ft_strdup(ms->input);
			ms->input = ft_free(ms->input);
			b = 2;
		}
		else
		{
			b = 0;
			if (len != 0)
				ms->input[len - 1] = '\0';
			if (i == 0 && !len && (ms->ctrl = CTRL_D))
				ft_exit(ms);
		}
	}
}
