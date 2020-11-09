/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:04:34 by yslati            #+#    #+#             */
/*   Updated: 2020/11/09 10:55:50 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				check_exist(char **env, char *arg)
{
	int i;
	// char	*wanted;

	// wanted = ft_strdup("");
	// wanted = ft_strcpy_pro(wanted, arg, '=');
	if (((i = get_env(env, arg)) != -1))
		return (i);
	return (-1);
}

char			**rm_arr(char **env, int pos)
{
	char 		**arr;
	int			i;
	int			j;
	int			len;

	i = 0;
	j = 0;
	len = tb_len(env) - 1;
	if (!(arr = (char **)malloc(sizeof(char **) * len + 1)))
		return (NULL);
	while (i < len)
	{
		if (j != pos)
			arr[i++] = ft_strdup(env[j]);
		j++;
	}
	arr[i] = NULL;
	return (arr);
}

int         ft_unset(t_ms *ms)
{
	int i;

	i = 0;
	if (ms->cmds->args[1])
	{
		if (ft_strchr(ms->cmds->args[1], '='))
			printf("minishell: unset: `%s': not a valid identifier\n", ms->cmds->args[1]);
		else if ((i = check_exist(ms->env, ms->cmds->args[1])) != -1)
		{
			//printf("i_get_env = %d\n", i);
			//i = get_env(env, ms->cmds->args[1]);
			dprintf(0, "%d == %s\n", i, ms->cmds->args[1]);
			ms->env = rm_arr(ms->env, i);
		}
		else
			puts("makinch had l3jb"); // print just new line 
	}
	else
		ft_putendl_fd("", 1);
	return 0;
}