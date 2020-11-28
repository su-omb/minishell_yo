/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:21:10 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/25 14:18:57 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		parse_scolon(t_ms *ms, int b, int i, char *s)
{
	char *tmp;

	tmp = ft_strldup(s + b, i - b);
	if (!(ms->tab = parse_split(tmp, ' ', ms)))
		errex(ms, SPLT_ERR);
	free(tmp);
}

void		parse_pipe(t_ms *ms, int b, int i, char *s)
{
	char *tmp;

	tmp = ft_strldup(s + b, i - b);
	if (!(ms->tab = parse_split(tmp, ' ', ms)))
		errex(ms, SPLT_ERR);
	free(tmp);
	ms->pp_count++;
}

void		parse_trunc_rdr(t_ms *ms, int b, int *i, char *s)
{
	char *tmp;

	ms->redir = TRUNC;
	if (s[*i + 1] == '>')
		ms->redir = APPEND;
	tmp = ft_strldup(s + b, *i - b);
	if (!(ms->tab = parse_split(tmp, ' ', ms)))
		errex(ms, SPLT_ERR);
	free(tmp);
	*i += (s[*i + 1] == '>');
}

void		parse_read_rdr(t_ms *ms, int b, int i, char *s)
{
	char *tmp;

	ms->redir = READ;
	tmp = ft_strldup(s + b, i - b);
	if (!(ms->tab = parse_split(tmp, ' ', ms)))
		errex(ms, SPLT_ERR);
	free(tmp);
}

void		new_cmd(t_ms *ms, char del, char **tab)
{
	t_cmd	*c;

	if (!(c = (t_cmd*)malloc(sizeof(t_cmd))))
		return ;
	c->next = NULL;
	c->cmd = ft_strdup(tab[0]);
	c->args = dup_str_tab(tab);
	c->redir = ms->redir;
	if (ms->cmds != NULL)
		c->start = (ms->cmds->end == 1) ? 1 : 0;
	else
		c->start = 1;
	c->end = (del == S_COLON) ? 1 : 0;
	if (ms->cmds)
		ms->cmds->next = c;
	c->prev = ms->cmds;
	c->is_err = ms->cmd_err != 0;
	c->is_status = ms->status;
	ms->cmds = c;
}

int		make_cmd(t_ms *ms, int b, int *i, char *s)
{
	if (s[*i] == S_COLON)
		parse_scolon(ms, b, *i, ms->input);
	else if (s[*i] == PIPE)
		parse_pipe(ms, b, *i, ms->input);
	else if (s[*i] == TRUNC)
		parse_trunc_rdr(ms, b, i, ms->input);
	else if (s[*i] == READ)
		parse_read_rdr(ms, b, *i, ms->input);
	
	if (ms->tab[0])
	{
		ms->cmd_err = ms->tab[0][0] == '\0';
		new_cmd(ms, s[*i], ms->tab);
	}
	free_str_table(ms->tab, tb_len(ms->tab));
	ms->tab = NULL;
	ms->redir = 0;
	ms->cmd_err = 0;
	return (*i + 1);
}

t_cmd		*get_head(t_cmd *cmds, char *err)
{
	if (cmds && cmds->is_err)
		*err = cmds->is_err;
	while (cmds && cmds->prev)
	{
		if (cmds->is_err)
			*err = cmds->is_err;
		cmds = cmds->prev;
	}
	return (cmds);
}

void	make_cmds_lst(t_ms *ms, t_parser *p)
{
	while (ms->input[p->i])
	{
		if (p->slash_ig)
			p->i++;
		p->slash_ig = 0;
		if (ms->input[p->i] == '\\' && ++p->i)
			p->slash_ig = 1;
		if (ms->input[p->i] && !p->slash_ig)
		{
			if (ft_strchr("'\"", ms->input[p->i]))
				p->i += quote_handler(ms->input + p->i, 0);
			if (ft_strchr("|;><", ms->input[p->i]))
			{
				make_cmd(ms, p->j, &p->i, ms->input);
				p->j = p->i + 1 + skip_while(ms->input + p->i + 1, ' ');
			}
		}
		if (!p->slash_ig)
			p->i++;
	}
}

void		make_last_cmd(t_ms *ms, t_parser *p)
{
	if (!(ms->tab = parse_split(ms->input + p->j, ' ', ms)))
		errex(ms, SPLT_ERR);
	new_cmd(ms, S_COLON, ms->tab);
}

void		parse(t_ms *ms)
{
	t_parser p;

	parse_d(ms);
	init_parser(&p);
	make_cmds_lst(ms, &p);
	if (ms->input[p.j])
		make_last_cmd(ms, &p);
	ms->lst_end = ms->cmds;
	ms->cmds = get_head(ms->cmds, &ms->cmd_err);
	/* Debug */
	print_cmds(ms->cmds);
}
