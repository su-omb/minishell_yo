/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:12:10 by obouykou          #+#    #+#             */
/*   Updated: 2020/06/08 14:46:51 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	int		l;

	l = 0;
	while (s[l])
		l++;
	if (s[l] == c)
		return ((char *)(s + l));
	while (--l >= 0)
		if (s[l] == c)
			return ((char *)(s + l));
	return (NULL);
}
