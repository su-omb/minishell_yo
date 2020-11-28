/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 09:35:39 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/26 09:35:39 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	parse_exec(t_ms *ms)
{
	int i;

	if (parse_total_cmds(ms))
	{
		clean_stx_err(ms);
		init(ms, 1, NULL);
		return ;
	}
	if (ms->cmd_tab)
	{
		i = -1;
		while(ms->cmd_tab[++i])
		{
			ms->input = ms->cmd_tab[i];
			parse(ms);
			if (ms->cmd_err || (ms->lst_end && !ms->lst_end->end))
			{
				clean_stx_err(ms);
				break ;
			}
			exec_command(ms);
			free_cmds(ms);
		}
	}
	init(ms, 2, NULL);
}

int		minishell(char **env, int step)
{
	t_ms	*ms;

	ms = (t_ms*)malloc(sizeof(t_ms));
	if (!step)
		init(ms, 0, env);
	while (1)
	{
		if (ms->skip != 130 && ms->skip != 131)
			ft_putstr_fd("\033[1;31m$minishell$~> \033[0m", 1);
		parse_exec(ms);
	}
	return (0);
}

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("\033[1;31m$minishell$~> \033[0m", 1);
	}
	else if (sig == SIGQUIT)
	{
		puts("l3iba");
	}
}

int		main(int ac,char **av, char **env)
{
	ac = 0;
	av = NULL;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	minishell(env, 0);
	return(0);
}
