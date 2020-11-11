/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:48:45 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/11 20:33:41 by obouykou         ###   ########.fr       */
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

	printf("var_name==> |%s|\n", var_name);
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
	tmp = (char *)malloc(l + 1);
	ft_bzero(tmp, l + 1);
	ft_strlcpy(tmp, input, *i);
	ft_strcat(tmp, varv);
	ft_strcat(tmp, input + *i + name_len);
	*i += ft_strlen(varv) - 1;
	free(input);
	free(varv);
	return (tmp);
}

char	*remove_bslash(char *input, int *i)
{
	char *tmp;

	if (ft_strchr("'\"", input[*i + 1]))
	{
		if (!input[*i + 1])
		{
			puts("Error: backslash at the end of a line command !\n");
			(*i)++;
		}
		else
			puts("Warning bslash is behind quote\n") && ++*i;
		return (input);
	}
	tmp = ft_strdup(input);
	tmp[(*i)++] = '\0';
	ft_strcat(tmp, input + *i);
	free(input);
	return (tmp);
}

void	parse_d(t_ms *ms)
{
	int i;
	int l;

	i = 0;
	while (ms->input[i])
	{
		if (ms->input[i] == '\\')
		{
			ms->input = remove_bslash(ms->input, &i);
			continue ;
		}
		if (((i && ms->input[i - 1] != '\\') || !i) && ms->input[i] == '\'')
				i += quote_handler(ms->input + i);
		if (ms->input[i] == '$' && ((i && ms->input[i - 1] != '\\') || !i))
		{
			if (ms->input[i + 1] == '?' && i++ && (ms->status = 1))
				continue ;
			l = skip_till(ms->input + ++i, " '\\$><|;");
			ms->input = remake_input(ms->input, get_vvalue(ft_strldup(ms->input + i, l), ms->env, l), l, &i);
		}
		else
			i++;
	}
}
