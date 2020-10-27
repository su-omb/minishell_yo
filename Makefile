# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/08 13:24:31 by obouykou          #+#    #+#              #
#    Updated: 2020/06/08 13:24:31 by obouykou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

LIB = libminishell.a

LIBFT = ./libft/libft.a

MS_MAIN = minishell.c

FILES = $(wildcard ./srcs/*.c ./srcs/*/*.c)

HEADER = ./includes/minishell.h

OBJECT = $(FILES:.c=.o)

FLAGS = -Wextra -Werror -Wall

all: $(NAME)
	@make -C ./libft

$(NAME): $(OBJECT) $(HEADER)
	@ar -rcs $(LIB) $(OBJECT)
	@echo "hello"
	@gcc  $(FLAGS) $(MS_MAIN) $(LIBFT) $(LIB) -o $(NAME)
	@echo "\n\033[32m------- Minishell has been created successfully -------\033[0m\n"

bonus: all

%.o:%.c $(HEADER)								
	@gcc -c $< $(FLAGS) 

clean:
	@rm -rf srcs/*.o $(LIB) $(LIBFT)
	@echo "\n\033[36mCleaning objects Done!\033[0m\n"

fclean: clean
	@rm -rf $(NAME)

re : fclean all