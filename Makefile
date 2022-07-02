# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/24 18:03:09 by youskim           #+#    #+#              #
#    Updated: 2022/06/27 23:28:06 by youskim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -Werror -Wall -Wextra 

INCLUDE = -I/Users/youskim/.brew/opt/readline/include
LIB = -L/Users/youskim/.brew/opt/readline/lib

# -g -fsanitize=address
# gcc test.c -L/Users/youskim/.brew/opt/readline/lib -I/Users/youskim/.brew/opt/readline/include -lreadline

FILE = main.c \
		make_node.c \
		make_redirect.c \
		change_input.c \
		change_quote.c \
		env_change_1.c \
		env_change_2.c \
		make_env.c \
		exe_cmd_1.c \
		exe_cmd_2.c \
		do_redirection.c \
		file_open.c \
		error.c \
		check_1.c \
		check_2.c \
		bt_echo_and_pwd.c \
		bt_env_and_unset.c \
		bt_exit.c \
		bt_export_1.c \
		bt_export_2.c \
		bt_cd.c \
		signal.c \
		do_execve.c \
		reset.c

OBJS = $(FILE:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C ./libft all
	$(CC) $(OBJS) $(INCLUDE) $(LIB) -lreadline -L./libft -lft -o $(NAME)

%.o : %.c
	$(CC) -c $< -o $@ $(INCLUDE)

clean :
	@$(MAKE) -C ./libft clean
	rm -rf $(OBJS)

fclean :
	make clean
	@$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re
