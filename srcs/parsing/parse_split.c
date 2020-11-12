/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:58:28 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/12 14:08:18 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		quote_handler(char const *s)
{
	char	quote;
	int		i;

	//printf("String to quote_handler() ==>|%s|\n", s);
	i = 1;
	quote = s[0];
	while (s[i] && s[i] != quote)
		i++;
	if (!s[i])
	{
		printf("ERROR not finding the second quote !!\n");
		return (i - 1);
	}
	return (i);
}

int		ft_words(char const *s, char c)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (((i && s[i - 1] != '\\') || !i) && (s[i] == '\'' || s[i] == '"'))
			i += quote_handler(s + i);
		if ((((i && s[i - 1] != '\\') && (s[i] == c && s[i + 1] != c))) || s[i + 1] == '\0')
			len++;
		i++;
	}
	return (len);
}

char	**ft_exception(char const *s)
{
	char	**tab;

	tab = NULL;
	if (!s)
	{
		tab = (char **)malloc(1 * sizeof(char *));
		tab[0] = NULL;
	}
	return (tab);
}

char	**free_everything(char **tab, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int		ft_len_elem(char const *s, char c)
{
	int		i;
	int		size;
	int		ret;

	i = -1;
	size = 0;
	while (s[++i] && (s[i] != c || (i && s[i - 1] == '\\')))
	{
		if (((i && s[i - 1] != '\\') || !i) && (s[i] == '\'' || s[i] == '"'))
		{
			ret = quote_handler(s + i);
			size += ret;
			i += ret;
		}
		if (s[i] != c  || (i && s[i - 1] == '\\'))
			size++;
	}
	return (size);
}

char	*remove_bslash(char *elem, int *i, char *err)
{
	char *tmp;

	if (ft_strchr("'\"", elem[*i + 1]))
	{
		if (!elem[*i + 1])
		{
			*err = STX_ERR;
			puts("Error: backslash at the end of a line command !\n");
			(*i)++;
		}
		else
			puts("Warning: bslash is behind quote\n") && ++*i;
		return (elem);
	}
	tmp = ft_strdup(elem);
	tmp[(*i)++] = '\0';
	ft_strcat(tmp, elem + *i);
	free(elem);
	return (tmp);
}

char	*remove_quotes(char *elem, int *i, int e)
{
	char	*tmp;
	
	tmp = ft_strdup(elem);
	tmp[(*i)++] = '\0';
	ft_strcat(tmp, elem + *i);
	tmp[e - 1] = '\0';
	ft_strcat(tmp, elem + ++e);
	free(elem);
	*i = e - 2;
	return (tmp);
}

char	*parse_quote_bslash(char *elem, t_ms *ms)
{
	int		i;

	i = -1;
	//printf("Elem==>|%s|\n", elem);
	while (elem[++i])
	{
		if (ft_strchr("'\"", elem[i]) && ((i && elem[i - 1] != '\\') || !i))
			elem = remove_quotes(elem, &i, i + quote_handler(elem + i));
		if (elem[i] == '\\')
			elem = remove_bslash(elem, &i, &ms->cmd_err);
	}
	return elem;
}

char	*fill_elem(char **elem, char *s, char c, t_ms *ms)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (s[j] && (s[j] != c || (j && s[j - 1] == '\\')))
	{
		quote = 0;
		if (((j && s[j - 1] != '\\') || !j) && (s[j] == '\'' || s[j] == '"'))
		{
			quote = s[j];
			(*elem)[i++] = s[j++];
			while (s[j] && s[j] != quote)
				(*elem)[i++] = s[j++];
			if (s[j])
				(*elem)[i++] = s[j++];
		}
		if (s[j] && !quote)
			(*elem)[i++] = s[j++];
	}
	(*elem)[i] = '\0';
	*elem = parse_quote_bslash(*elem, ms);
	return (s + j);
}

char	**parse_split(char const *s, char c, t_ms *ms)
{
	char	**tab;
	int		j;
	int		l;

	if ((tab = ft_exception(s)))
		return (tab);
	l = ft_words(s, c);
	j = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (l + 1))))
		return (NULL);
	tab[l] = NULL;
	while (j < l)
	{
		while (*s && *s == c)
			s++;
		if (!(tab[j] = (char *)malloc((ft_len_elem(s, c) + 1) * sizeof(char))))
			return (free_everything(tab, l));
		s = fill_elem(&tab[j++], (char *)s, c, ms);
	}
	return (tab);
}
