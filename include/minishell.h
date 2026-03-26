/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: w <w@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:27:42 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/25 18:57:49 by w                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*	======	Macro Used	======	*/

# define EXIT "exit"
# define PROMPT "minishell> "

/*	======	Library Used	======	*/

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>

/*	======	Enumeration Used	======	*/

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

/*	======	Structure Used	======	*/

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

typedef struct s_command
{
	char	**args;
	char	*input;
	char	*output;
	int		append;
	int		heredoc;

}	t_command;

typedef struct s_pipeline
{
	t_command	*commands;
	int			nb_commands;
}	t_pipeline;

/*	======	Fonction Used	======	*/

	/*	Lexing Functions	*/

void		handle_multiligne_case(char **line, t_malloc **lst_malloc);
void		back_slash_case(char **line, char *word);
void		lexer(t_token **lst_token, t_malloc **lst_malloc, char **line);

		/*		lexer	2	*/

void		token_redir_out(t_token **token_lst, t_malloc **lst_malloc);
void		token_redir_heredeoc(t_token **token_lst, t_malloc **lst_malloc);
void		handle_redir_case(char **line, t_token **lst_token,
				t_malloc **lst_malloc);
void		token_operator(char **line, t_token **lst_token,
				t_malloc **lst_malloc);
void		token_append(t_token **token_lst, t_malloc **lst_malloc);

		/*		lexer	3	*/

void		token_pipe(t_token **token_lst, t_malloc **lst_malloc);
void		token_redir_in(t_token **token_lst, t_malloc **lst_malloc);
bool		are_quotes_closed(char *line);

	/*	Malloc Functions	*/

void		clean_lst_malloc(t_malloc *lst_malloc);
t_malloc	*create_node_malloc(void *address_malloc);
void		add_malloc_in_lst(t_malloc **lst_malloc, t_malloc *malloc_node);
void		*malloc_remix(size_t nb_octets, t_malloc **lst_malloc);
void		display_lst_malloc(t_malloc *lst_malloc);

	/*	Token Functions		*/

t_token		*create_token(char *word, int type,
				t_malloc **lst_malloc, t_token **token_lst);
void		display_token(t_token *token_lst);

	/*	Tools Functions		*/

bool		is_space(char c);
bool		is_quote(char c);
bool		is_single_quote(char c);
bool		is_double_quote(char c);
bool		is_operator(char c);

		/*		Tools	2	*/

int			ft_strlen(char *str);
char		*ft_strdup(char *str, t_malloc **lst_malloc);
char		*ft_strjoin(char *line, char *new_line, t_malloc **lst_malloc);
bool		ft_strcmp(char *s1, char *s2);
char		*remix_readline(const char	*prompt, t_malloc **lst_malloc);

		/*		Tools	3	*/

bool		is_back_slash(char c);
bool		ends_with_backslash(char *line);
bool		is_pipe(char c);
bool		is_redir_in(char c);
bool		is_redir_out(char c);

		/*		Tools	4	*/

bool		is_here_doc(char **line);
bool		is_append(char **line);
bool		is_redir(t_token *lst_token);

	/*	Error Functions		*/

bool		is_empty_list(t_token *lst_token);
void		check_syntax(t_token **lst_token, const char *prompt,
				char **line, t_malloc **lst_malloc);


		/*	pipe_error	*/

bool		check_pipe(t_token *lst_token, const char *prompt,
				char **line, t_malloc **lst_malloc);

		/*	Redir error	*/

bool		consecutive_redir(t_token *lst_token,
				char **bad_word, t_malloc **lst_malloc);
bool		last_token_is_redir(t_token *lst_token);
bool		check_redir(t_token *lst_token, const char *prompt,
				t_malloc **lst_malloc);

		/*	Incomplete input	*/

bool		last_char_is_pipe(char *line);
bool		is_incomplete_input(char *line);

#endif