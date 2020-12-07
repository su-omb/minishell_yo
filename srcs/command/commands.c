/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:56:00 by yslati            #+#    #+#             */
/*   Updated: 2020/12/07 13:37:55 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				is_builtin_sys(char *cmds)
{
	return (!(ft_strcmp(cmds, "env") && ft_strcmp(cmds, "cd") &&
		ft_strcmp(cmds, "pwd") && ft_strcmp(cmds, "export") &&
		ft_strcmp(cmds, "unset") && ft_strcmp(cmds, "echo") &&
		ft_strcmp(cmds, "exit")));
}

t_ms			*exucte_help(t_ms *ms)
{
	while (ms && ms->cmds->redir)
	{
		if (!ms->cmds->next)
			break ;
		ms->cmds = ms->cmds->next;
	}
	return (ms);
}

t_cmd			*exucte_cmd(t_ms *ms)
{
	while (ms->cmds)
	{
		if ((ms->cmds->start == 0 && ms->cmds->prev->redir)
			|| (ms->cmds->start && is_builtin_sys(ms->cmds->cmd)
			&& (!ms->cmds->redir && !ms->pp_count)))
			break ;
		ms->pid = run_child(ms, 0);
		ms = exucte_help(ms);
		if (ms->pid < 0)
		{
			ft_putstr_fd("minishell: forking error\n", 2);
			exit(0);
		}
		if (ms->cmds->end)
			break ;
		else
			ms->cmds = ms->cmds->next;
		ms->j += 2;
	}
	return (ms->cmds);
}

void			manage_cmd(t_ms *ms)
{
	int			st;
	int			i;

	st = 0;
	i = 0;
	save_fds(ms->backup);
	ms->cmds = exucte_cmd(ms);
	restore_fds(ms->backup);
	while (ms->pp_count && i < 2 * ms->pp_count)
		close(ms->fds[i++]);
	st = wait_child(ms);
	if (st == 2 || st == 3)
		ms->status = st + 128;
	else
		ms->status = (st >> 8) & 255;
}

void			exec_command(t_ms *ms)
{
	int			i;

	i = 0;
	if (!g_ret)
		g_ret = 2;
	if (ms->pp_count)
	{
		ms->fds = (int *)malloc((2 * ms->pp_count) * sizeof(int));
		ms->tpid = (pid_t *)malloc(sizeof(pid_t) * (ms->pp_count + 1));
	}
	if (ms->pp_count)
		while (i < 2 * ms->pp_count)
		{
			pipe(ms->fds + (i * 2));
			i += 1;
		}
	ms->j = 0;
	while (ms->cmds)
	{
		if ((ms->cmds->next && !ms->cmds->end) ||
		!is_builtin_sys(ms->cmds->cmd))
			manage_cmd(ms);
		if (is_builtin_sys(ms->cmds->cmd) && !ms->pp_count && !ms->cmds->redir)
			check_command(ms);
		ms->cmds = ms->cmds->next;
	}
	ms->cmds = ms->head;
}
