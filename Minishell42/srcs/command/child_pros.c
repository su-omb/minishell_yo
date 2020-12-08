/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_pros.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 13:36:41 by yslati            #+#    #+#             */
/*   Updated: 2020/12/07 13:41:14 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				*dup_in_out(t_ms *ms)
{
	if (ms->j != 0)
		if (dup2(ms->fds[ms->j - 2], 0) < 0)
		{
			perror("dup2");
			exit(1);
		}
	if (ms->cmds->next && (ms->pp_count || !ms->cmds->end))
		if (dup2(ms->fds[ms->j + 1], 1) < 0)
		{
			perror("dup2");
			exit(1);
		}
	return (ms->fds);
}

pid_t			run_child(t_ms *ms, int i)
{
	pid_t		pid;
	t_cmd		*tmp;

	tmp = ms->cmds;
	pid = fork();
	if (pid == 0)
	{
		if (ms->pp_count)
			ms->fds = dup_in_out(ms);
		if (ms->cmds->redir)
			ft_redir(ms, tmp, ms->cmds);
		while (ms->pp_count && i < 2 * ms->pp_count)
			close(ms->fds[i++]);
		if (ms->cmds->args && check_command(ms)
		&& !is_builtin_sys(ms->cmds->cmd))
		{
			cmd_error(ms, CMD_NOT_FOUND_ERR, NULL, ms->cmds->cmd);
			exit(127);
		}
		exit(0);
	}
	if (ms->pp_count)
		ms->tpid[ms->j / 2] = pid;
	return (pid);
}

int				wait_child(t_ms *ms)
{
	int			st;
	int			i;

	st = 0;
	i = -1;
	if (!ms->pp_count)
	{
		waitpid(ms->pid, &st, 0);
	}
	else
		while (++i < ms->pp_count + 1)
		{
			waitpid(ms->tpid[i], &st, 0);
			if (st == 2)
				return (2);
		}
	return (st);
}
