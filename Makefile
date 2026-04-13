# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/14 14:18:21 by wngambi           #+#    #+#              #
#    Updated: 2026/04/13 08:14:33 by wngambi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	------	Artistique	------	#

RED = \033[31m
GREEN = \033[32m
CYAN = \033[36m
RESET = \033[0m
ORANGE = \033[33m
PURPLE =  \033[0;35m
define ASCII_ART
$(RED) 




████████████████████████████████████████
█▌░█▄█░▀█▀░█▀█░▀█▀░█▀▀░█░█░█▀▀░█░░░█░░▐█
█▌░█░█░░█░░█░█░░█░░▀▀█░█▀█░█▀▀░█░░░█░░▐█
█▌░▀░▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀▀▀▐█
████████████████████████████████████████





$(RESET)
endef
export ASCII_ART

#	------	Artistique	------	#


# Makefile #

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS	=	-lreadline
RM		=	rm -rf


# All Directories #

HEADER_DIR = includes

NAME	=	minishell
HEADER	=	$(HEADER_DIR)/minishell.h

SRC =	main.c \
	src/signals/signals.c \
	$(wildcard src/builtins/*.c) \
	$(wildcard src/executor/*.c) \
	$(wildcard src/env/*.c) \
	$(wildcard src/src_parser/*.c) \
	$(wildcard src/merger/*.c)

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

#	Compilation Rules	#

all:
	@echo "$$ASCII_ART"
	@echo "$(GREEN)Hello $$(whoami) !$(RESET)"
	@echo "$(GREEN)Compiling Minishell...$(RESET)"
	@$(MAKE) $(NAME)
	@echo "$(CYAN)Compilation completed!$(RESET)"
	
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -Llibft -lft -o $(NAME) $(LDFLAGS)
$(LIBFT):
	make -C libft

%.o: %.c $(HEADER)
	@echo "$(PURPLE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@

clean:
	@echo "$(GREEN)Cleaning...$(RESET)"
	make clean -C libft
	$(RM) $(OBJ)
	@echo "$(CYAN)Cleaned successfully!$(RESET)"

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re