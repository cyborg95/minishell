/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:23:48 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/01 14:23:49 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* MACROS */

# define EXIT "exit"
# define PROMPT "minishell> "

/* LIBRARIES */

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>

/* ENUM */

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	EXPAND
}	t_type;

/* STRUCT */

typedef struct s_token	t_token;
typedef struct s_malloc	t_malloc;
typedef struct s_redir	t_redir;
typedef struct s_cmd	t_cmd;

struct s_token
{
	char	*word;
	t_type	type;
	t_token	*next;
};

struct s_malloc
{
	void		*adress_malloc;
	t_malloc	*next;
};

struct s_redir
{
	int		type;
	char	*file;
	t_redir	*next;
};

struct s_cmd
{
	char		**args;
	t_redir		*redir;
	t_cmd		*next;
};

/* COMMAND */

t_cmd		*create_cmd(t_malloc **lst_malloc, t_token *lst_token);
void		fill_cmd(t_token **lst_token, t_cmd *cmd, t_malloc **lst_malloc);
void		add_back_cmd(t_cmd **lst_cmd, t_cmd *cmd, t_malloc **lst_malloc);
void		display_cmd(t_cmd *cmd_lst);

/* ERROR */

bool		is_empty_list(t_token *lst_token);
bool		check_token_lst(t_token **lst_token, const char *prompt,
				char **line, t_malloc **lst_malloc);

/* LEXER */

bool		are_quotes_closed(char *line);
void		handle_multiligne_case(char **line, t_malloc **lst_malloc);
void		back_slash_case(char **line, char *word);

void		lexer(t_token **lst_token, t_malloc **lst_malloc, char **line);
void		token_pipe(t_token **token_lst, t_malloc **lst_malloc);
void		token_redir_in(t_token **token_lst, t_malloc **lst_malloc);

void		token_redir_out(t_token **token_lst, t_malloc **lst_malloc);
void		token_redir_heredeoc(t_token **token_lst, t_malloc **lst_malloc);
void		handle_redir_case(char **line, t_token **lst_token,
				t_malloc **lst_malloc);
void		token_operator(char **line, t_token **lst_token,
				t_malloc **lst_malloc);
void		token_append(t_token **token_lst, t_malloc **lst_malloc);

/* MALLOC */

void		clean_lst_malloc(t_malloc *lst_malloc);
t_malloc	*create_node_malloc(void *address_malloc);
void		add_malloc_in_lst(t_malloc **lst_malloc, t_malloc *malloc_node);
void		*malloc_remix(size_t nb_octets, t_malloc **lst_malloc);
void		display_lst_malloc(t_malloc *lst_malloc);

/* PIPE ERROR */

bool		check_pipe(t_token *lst_token, const char *prompt,
				char **line, t_malloc **lst_malloc);

/* REDIR ERROR */

bool		consecutive_redir(t_token *lst_token,
				char **bad_word, t_malloc **lst_malloc);
bool		last_token_is_redir(t_token *lst_token);
bool		check_redir(t_token *lst_token,
				const char *prompt, t_malloc **lst_malloc);

/* REDIR */

void		handle_redir(t_malloc **lst_malloc, t_token **lst_token,
				t_cmd *cmd);
t_redir		*create_redir(t_malloc **lst_malloc, int token_type);
void		add_back_redir(t_cmd *cmd, t_redir *new_redir);
void		display_redir(t_cmd *cmd);

/* TOKEN */

t_token		*create_token(char *word, int type,
				t_malloc **lst_malloc, t_token **token_lst);
void		display_token(t_token *token_lst);

/* TOOLS */

bool		is_space(char c);
bool		is_quote(char c);
bool		is_single_quote(char c);
bool		is_double_quote(char c);
bool		is_operator(char c);
int			ft_strlen(char *str);
char		*ft_strdup(char *str, t_malloc **lst_malloc);
char		*ft_strjoin(char *line, char *new_line, t_malloc **lst_malloc);
bool		ft_strcmp(char *s1, char *s2);
char		*remix_readline(const char *prompt, t_malloc **lst_malloc);
bool		is_back_slash(char c);
bool		ends_with_backslash(char *line);
bool		is_pipe(char c);
bool		is_redir_in(char c);
bool		is_redir_out(char c);
bool		is_here_doc(char **line);
bool		is_append(char **line);
bool		is_redir(t_token *lst_token);
void		ft_bzero(void *s, size_t n);
void		display_args(char **args);

#endif