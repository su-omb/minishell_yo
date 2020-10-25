/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 13:32:40 by obouykou          #+#    #+#             */
/*   Updated: 2020/06/08 13:32:40 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void		init(t_ms *ms)
{
	ms->ret = 0;
	ms->is_op = 0;
	ms->tab = NULL;
}

void		minishell(char **av, char **env)
{
	t_ms ms;

	parse(av);
	while (1)
	{
		init(&ms);
		ft_putstr_fd("$minishell$~> ", 1);
		get_input(&ms);
		ft_cmd(&ms);
	}
}

int		main(int ac, char **av, char **env)
{
	minishell(av, env);
	puts("");
	return(0);
}