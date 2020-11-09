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

void		minishell(char **env, int step)
{
	t_ms	ms;

	if (!step)
		init(&ms, 0, env);
	while (1)
	{
		ft_putstr_fd("\033[1;31m$minishell$~> \033[0m",1);
		parse(&ms);
		if (ms.input[0] == '\0')
			continue ;
 		else if (!ft_strcmp(ms.cmds->cmd, "clear") || !ft_strcmp(ms.cmds->cmd, "cl"))
			ft_putstr_fd("\e[1;1H\e[2J",1);
		else
			check_command(&ms);
		init(&ms, 1, NULL);
		//ms.cmds ? free_ms(ms) : 0 ;
	}

}

int		main(int ac,char **av, char **env)
{
	ac = 0;
	av = NULL;
	minishell(env, 0);
	return(0);
}
