# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/14 14:18:21 by wngambi           #+#    #+#              #
#    Updated: 2026/04/13 08:27:34 by wngambi          ###   ########.fr        #
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

SRC_DIR =	src


SRC =	$(SRC_DIR)/builtins/builtin_utils.c \
		$(SRC_DIR)/builtins/cd.c \
		$(SRC_DIR)/builtins/echo.c \
		$(SRC_DIR)/builtins/env.c \
		$(SRC_DIR)/builtins/exit.c \
		$(SRC_DIR)/builtins/export.c \
		$(SRC_DIR)/builtins/pwd.c \
		$(SRC_DIR)/builtins/unset.c \
		$(SRC_DIR)/builtins/utils.c \
		$(SRC_DIR)/env/env_init.c \
		$(SRC_DIR)/env/env_list.c \
		$(SRC_DIR)/env/env_utils.c \
		$(SRC_DIR)/env/expand_helper.c \
		$(SRC_DIR)/executor/execute_command.c \
		$(SRC_DIR)/executor/execute_node.c \
		$(SRC_DIR)/executor/execute_pipe.c \
		$(SRC_DIR)/executor/executor.c \
		$(SRC_DIR)/executor/external_exec.c \
		$(SRC_DIR)/executor/redirections.c \
		$(SRC_DIR)/merger/merger.c \
		$(SRC_DIR)/signals/signals.c \
		$(SRC_DIR)/src_parser/command.c \
		$(SRC_DIR)/src_parser/error.c \
		$(SRC_DIR)/src_parser/incomplete_input.c \
		$(SRC_DIR)/src_parser/lexer.c \
		$(SRC_DIR)/src_parser/lexer2.c \
		$(SRC_DIR)/src_parser/lexer3.c \
		$(SRC_DIR)/src_parser/malloc.c \
		$(SRC_DIR)/src_parser/parsing_minishell.c \
		$(SRC_DIR)/src_parser/pipe_error.c \
		$(SRC_DIR)/src_parser/pipe_error2.c \
		$(SRC_DIR)/src_parser/redir_error.c \
		$(SRC_DIR)/src_parser/redir.c \
		$(SRC_DIR)/src_parser/token.c \
		$(SRC_DIR)/src_parser/tools.c \
		$(SRC_DIR)/src_parser/tools2.c \
		$(SRC_DIR)/src_parser/tools3.c \
		$(SRC_DIR)/src_parser/tools4.c \
		$(SRC_DIR)/src_parser/tools5.c \
		main.c 

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