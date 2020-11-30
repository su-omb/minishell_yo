/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:03:01 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/30 20:38:36 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_parser(t_parser *p)
{
	p->i = 0;
	p->j = 0;
	p->m = 0;
	p->quote_ig = 0;
	p->slash_ig = 0;
	p->l = 0;
}

void	free_cmds(t_ms *ms)
{
	t_cmd *c;

	c = ms->cmds;
	while (c)
	{
		free(c->cmd);
		c->cmd = NULL;
		free_str_table(c->args, tb_len(c->args));
		c = c->next;
	}
	if (c)
		free(ms->cmds);
}

void	init_zero(t_ms *ms, char **env)
{
	ms->status = 0;
	ms->input = (char *)malloc(SIZE);
	ms->env = dup_str_tab(env);
	ms->pwd = getcwd(NULL, 0);
	ms->old_pwd = NULL;
	ms->cmd_tab = NULL;
	ms->tab = NULL;
	ms->ret_status = 0;
}

void	init(t_ms *ms, char step, char **env)
{
	ms->err = 0;
	ms->cmd_err = 0;
	ms->cmds = NULL;
	ms->redir = 0;
	ms->pp_count = 0;
	if (!step)
		init_zero(ms, env);
	if (step == 1)
	{
		ms->input = (char *)malloc(SIZE);
	}
	if (step == 2)
	{
		ms->input = (char *)malloc(SIZE);
		if (ms->tab)
			free_str_table(ms->tab, tb_len(ms->tab));
		ms->cmd_tab = NULL;
		ms->tab = NULL;
	}
}
