/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_total_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:21:10 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/28 10:07:09 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			skip_while(char *s, char c)
{
	int i;
	
	i = 0;
	while (s[i] == c)
		++i;
	return (i);
}

void		get_input(t_ms *ms)
{
	int i;

	if ((i = read(0, ms->input, SIZE)) < 0)
	{
		ms->err = RDIN_ERR;
		errex(ms, 0);
	}
	ms->input[i - 1] = '\0';
}

int		sm_finder(char *input, t_parser *p)
{
	int		r;

	if (input[p->i] && ft_strchr("'\"", input[p->i]))
	{
		if ((r = quote_handler(input + p->i, 1)) < 0)
			return (STX_ERR);
		p->i += r;
	}
	if (input[p->i] == ';')
	{
		p->j = p->i + 1;
		p->m = p->j + skip_while(input + p->j, ' ');
		if (input[p->m] == ';')
			return (STX_ERR);
		p->l++;
	}
	return (SUCCESS);
}

int		get_hm_cmds(char *input, t_parser *p)
{
	init_parser(p);
	while (input[p->i])
	{
		if (p->slash_ig)
			p->i++;
		p->slash_ig = 0;
		if (input[p->i] == '\\' && ++p->i)
			p->slash_ig = 1;
		if (!p->slash_ig)
			if (sm_finder(input, p) == STX_ERR)
				return (-1);
		if (!p->slash_ig)
			p->i++;
	}
	if (input[p->m])
		p->l++;
	return (p->l);
}

int		stx_handler(char **input, t_parser *p)
{
	p->m = input[0][skip_while(*input, ' ')];
	if (!p->m || p->m == ';')
	{
		free(*input);
		*input = NULL;
		return (!p->m ? 0 : STX_ERR);
	}
	if (get_hm_cmds(*input, p) < 0)
	{
		free(*input);
		*input = NULL;
		return (STX_ERR);
	}
	return (VALID_STX);
}

int		parse_total_cmds(t_ms *ms)
{
	t_parser p;

	get_input(ms);
	if ((p.m = stx_handler(&ms->input, &p)) != VALID_STX)
		return (p.m);
	ms->cmd_tab = (char **)malloc(sizeof(char *) * (p.l + 1));
	ms->cmd_tab[p.l] = NULL;
	init_parser(&p);
	p.i = -1;
	while (ms->input[++p.i])
	{
		if (ft_strchr("'\"", ms->input[p.i]) && ((p.i && ms->input[p.i - 1] != '\\') || !p.i))
			p.i += quote_handler(ms->input + p.i, 1);
		if (';' == ms->input[p.i] && ((p.i && ms->input[p.i - 1] != '\\') || !p.i))
		{
			ms->cmd_tab[p.m++] = ft_substr(ms->input, p.j, p.i - p.j + 1);
			p.j = p.i + 1 + skip_while(ms->input + p.i + 1, ' ');
		}
	}
	if (ms->input[p.j])
		ms->cmd_tab[p.m] = ft_substr(ms->input, p.j, p.i - p.j + 1);
	free(ms->input);
	ms->input = NULL;
	print_total_cmds(ms->cmd_tab);
	return (0);
}
