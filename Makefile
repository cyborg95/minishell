# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/14 14:18:21 by wngambi           #+#    #+#              #
#    Updated: 2026/04/02 07:20:17 by wngambi          ###   ########.fr        #
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

SRC	=	$(SRC_DIR)/command.c \
		$(SRC_DIR)/error.c \
		$(SRC_DIR)/lexer.c \
		$(SRC_DIR)/lexer2.c \
		$(SRC_DIR)/lexer3.c \
		$(SRC_DIR)/malloc.c \
		$(SRC_DIR)/parsing_minishell.c \
		$(SRC_DIR)/pipe_error.c \
		$(SRC_DIR)/redir_error.c \
		$(SRC_DIR)/redir.c \
		$(SRC_DIR)/token.c \
		$(SRC_DIR)/tools.c \
		$(SRC_DIR)/tools2.c \
		$(SRC_DIR)/tools3.c \
		$(SRC_DIR)/tools4.c \
		$(SRC_DIR)/tools5.c \
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