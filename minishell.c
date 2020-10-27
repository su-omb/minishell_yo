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

void		init(t_ms *ms)
{
	ms->ret = 0;
	ms->is_op = 0;
	ms->tab = NULL;
}

void		minishell(char **av, char **env)
{
	t_ms ms;

	//parse(av);
	av[0] = NULL;
	env[0] = NULL;
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
	if(ac)
	minishell(av, env);
	return(0);
}