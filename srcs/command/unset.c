/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:04:34 by yslati            #+#    #+#             */
/*   Updated: 2020/11/10 11:27:47 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				check_exist(char **env, char *arg)
{
	int i;
	char	*wanted;

	wanted = ft_strdup("");
	wanted = ft_strcpy_pro(wanted, arg, '=');
	if (((i = get_env(env, wanted)) != -1))
	{
		printf("\n CH ;;;; env[%i]: %s -- wanted: %s\n", i, env[i], wanted);
		//printf("\ni = %d\n", i);
		return (i);
	}
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
		{
			ft_putstr_fd("minishell: unset: `", 1);
			ft_putstr_fd(ms->cmds->args[1], 1);
			ft_putendl_fd("': not a valid identifier", 1);
		}
		else if ((i = check_exist(ms->env, ms->cmds->args[1])) != -1)
			ms->env = rm_arr(ms->env, i);
		else
			ft_putendl_fd("", 1);
	}
	else
		ft_putendl_fd("", 1);
	return 0;
}
