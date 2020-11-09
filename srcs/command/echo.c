/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:11:49 by yslati            #+#    #+#             */
/*   Updated: 2020/11/09 14:33:28 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int			check_n(char **args, int *i)
{
	int nflag;

	nflag = 0;
	while (!ft_strncmp(args[*i], "-n", 2))
	{
		*i = *i + 1;
		nflag = 1;
	}
	return (nflag);
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

	while (ms->cmds)
	{
		file = open(ms->cmds->next->cmd, O_WRONLY | O_CREAT, 0666);
		printf("cmd in redir |%s| %d | string: |%s|\n", ms->cmds->next->cmd, i, ms->cmds->args[i]);
		write(file, ms->cmds->args[i], ft_strlen(ms->cmds->args[i]));
		write(file, "\n", 1);
		if (ms->cmds->next->cmd)
		{
			ms->cmds = ms->cmds->next;
			i++;
		}
	}
}

void			ft_echo(t_ms *ms)
{
	int i;
	int nflag;

	i = 1;
	nflag = 0;
	if (ms->cmds->redir == TRUNC)
		redir(ms, i);
	else
	{
		if (!ms->cmds->args[i])
			ft_putendl_fd("", 1);
		
		else if (ms->cmds->args[i])
		{
			nflag = check_n(ms->cmds->args, &i);
			while (ms->cmds->args[i])
			{
				ft_putstr_fd(ms->cmds->args[i], 1);
				if (ms->cmds->args[i + 1])
					ft_putchar_fd(' ', 1);
				i++;
			}
			if (!nflag)
				ft_putchar_fd('\n', 1);
		}
		
	}
}
