# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/04 14:51:58 by otidahoh          #+#    #+#              #
#    Updated: 2026/03/09 11:43:37 by otidahoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
NAME = minishell

SRCS = main.c \
	src/signals/signals.c \
	$(wildcard src/builtins/*.c) \
	$(wildcard src/executor/*.c) \
	$(wildcard src/env/*.c) \
	
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

INCLUDES = includes/*.h
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -lreadline -o $(NAME)
$(LIBFT):
	make -C libft

%.o: %.c ${INCLUDES}
	${CC} ${CFLAGS} -c $< -o $@
clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all