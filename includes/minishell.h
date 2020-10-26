/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 13:24:51 by obouykou          #+#    #+#             */
/*   Updated: 2020/06/08 13:24:51 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
#include "../libft/libft.h"

# define SIZE 4194304
# define HELLO "\n======> SAFE <======"

typedef struct	s_ms
{
	char	input[SIZE];
	char	output[SIZE];
	char	cmd[256];
	char	op[256];
	short	is_op;
	char	path[4096];
	char	str[1048576];
	char	*ptr;
	char	**tab;
	int		ret;
}				t_ms;

void		get_input(t_ms *ms);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
size_t		ft_strlen(const char *s);
void		ft_putendl_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
int			tb_len(char **table);
char		**free_str_table(char **tab, int size);
void		ft_exit(t_ms *ms);
void		ft_echo(t_ms *ms);
void		ft_cmd(t_ms *ms);
int			ft_atoi(const char *str);


#endif
