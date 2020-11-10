/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:48:45 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/10 14:46:55 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		skip_till(char *s, char *set)
{
	int i;

	i = -1;
	while (s[++i])
		if (ft_strchr(set, s[i]))
			return (i);
	return (i);
}

char	*get_vvalue(char *var_name, char **env, int l)
{
	int i;

	if ((i = get_env(env, var_name)) < 0)
		return (ft_strdup(""));
	free(var_name);
	return (ft_strdup(env[i] + l + 1));
}

char	*remake_input(char *input, char *varv, int name_len, int *i)
{
	int		l;
	char	*tmp;
	
	l = ft_strlen(input) - name_len + ft_strlen(varv) - 1;
	//printf("\ninput_len=|%zu|\tl+1=|%d|\tvarv_len=|%zu|",ft_strlen(input), l + 1, ft_strlen(varv));
	tmp = (char *)malloc(l + 1);
	ft_bzero(tmp, l + 1);
	ft_strlcpy(tmp, input, *i);
	ft_strcat(tmp, varv);
	//printf("\ntmp>>>>>|%s|\tname_len =|%d|\t i=|%d|\tpos_str=|%s|\n",
	// tmp, name_len, *i, input + *i + name_len);
	ft_strcat(tmp, input + *i + name_len);
	*i += ft_strlen(varv);
	//printf("tmp+i = |%s|\n", tmp + *i);
	free(input);
	free(varv);
	return (tmp);
}

void	parse_d(t_ms *ms)
{
	int i;
	int l;

	i = 0;
	while (ms->input[i])
	{
		if (ms->input[i] == '\'' && ++i)
			while (ms->input[i] != '\'')
				i++;
		if (ms->input[i] == '$' && (i && ms->input[i - 1] != '\\'))
		{
			//printf("input + i : |%s|\n", ms->input+i);
			if (ms->input[i + 1] == '?' && i++ && (ms->status = 1))
				continue ;
			l = skip_till(ms->input + ++i, " '\\$><|;");
			ms->input = remake_input(ms->input, get_vvalue(ft_strldup(ms->input + i, l), ms->env, l), l, &i);
			if (ms->input[i - 1] == '$')
				i--;
			//printf("====> New input : |%s|%d|\n", ms->input, i);
		}
		else
			i++;
	}
}

// echo /Users/obouykou/Desktop/minishell_yo
//echo $PWD