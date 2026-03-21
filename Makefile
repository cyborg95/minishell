# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/14 14:18:21 by wngambi           #+#    #+#              #
#    Updated: 2026/03/21 18:20:24 by wngambi          ###   ########.fr        #
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
CFLAGS	=	-Wall -Wextra -Werror -g
LDFLAGS	=	-lreadline
RM		=	rm -rf


# All Directories #

HEADER_DIR	=	include
SRC_DIR		=	src

#	Files	#

NAME	=	minishell
HEADER	=	$(HEADER_DIR)/minishell.h

SRC	=	$(SRC_DIR)/lexer.c \
		$(SRC_DIR)/lexer2.c \
		$(SRC_DIR)/malloc.c \
		$(SRC_DIR)/token.c \
		$(SRC_DIR)/tools.c \
		$(SRC_DIR)/tools2.c \
		main.c

OBJ	=	$(SRC:.c=.o)

#	Compilation Rules	#

all:
	@echo "$$ASCII_ART"
	@echo "$(GREEN)Hello $$(whoami) !$(RESET)"
	@echo "$(GREEN)Compiling Minishell...$(RESET)"
	@$(MAKE) $(NAME)
	@echo "$(CYAN)Compilation completed!$(RESET)"
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c $(HEADER)
	@echo "$(PURPLE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@

clean:
	@echo "$(GREEN)Cleaning...$(RESET)"
	$(RM) $(OBJ)
	@echo "$(CYAN)Cleaned successfully!$(RESET)"

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re