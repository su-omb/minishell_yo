/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:11:49 by yslati            #+#    #+#             */
/*   Updated: 2020/11/09 13:08:19 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void			echo_n(t_ms *ms)
{
	int		i;

	i = 2;
	while (!ft_strncmp(ms->cmds->args[i], "-n", 2))
		i++;
	if (!ms->cmds->args[i])
		ft_putstr_fd("", 1);
	else
		ft_putstr_fd(ms->cmds->args[i], 1);
}

/* void			echo_dollar(t_ms *ms, int i)
{
	char	*tmp;
	int		j;
	//int		len;

	tmp = ft_strdup("");
	if ((tmp = ft_strcpy_pro(tmp, ms->cmds->args[i], '$')) && (!ft_strcmp("", tmp)))
	{
		puts("$ is first");
		j = get_env(ms->env, ms->cmds->args[i] + 1);
		//len = 
		ft_putendl_fd(ms->env[j] + ft_strlen(ms->cmds->args[i] + 1) + 1, 1);
	}
	else
	{
		puts("something befor $");
	}

} */

void			redir(t_ms *ms, int i)
{
	int		file;

	// printf("cmd in redir |%s| %d | string: |%s|\n", ms->cmds->next->cmd, i, ms->cmds->args[i]);
	file = open(ms->cmds->next->cmd, O_WRONLY | O_CREAT, 0666);
	write(file, ms->cmds->args[i], ft_strlen(ms->cmds->args[i]));
	write(file, "\n", 1);
}

void			ft_echo(t_ms *ms)
{
	int i;

	i = 1;
	if (ms->cmds->redir == TRUNC)
		redir(ms, i);
	else
	{
		if (!ms->cmds->args[i])
			ft_putendl_fd("", 1);
		
		else if (ms->cmds->args[i])
		{
			if (!ft_strncmp(ms->cmds->args[i], "-n", 2))
				echo_n(ms);
			/* else if (!ft_strchr(ms->cmds->args[i], '$'))
				echo_dollar(ms, i); */
			else
				ft_putendl_fd(ms->cmds->args[i], 1);
			//i++;
		}
	}
}
