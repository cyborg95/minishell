/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:44:15 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/27 12:26:23 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "builtins.h"
# include "executor.h"
# include "structs.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

t_env		*init_env(char **envp);
char		**env_list_to_array(t_env *env);
void		ft_free_tab(char **tab);
void		free_env_list(t_env *env);
int			ft_1strcmp(const char *s1, const char *s2);
void		add_or_update_env(t_shell *shell, char *key, char *value);
char		*my_getenv(char *name, char **env);
void		handle_signal(int sig);
void		expand_tree(t_node *node, t_shell *shell);
int			is_valid_identifier(char *str);
int			printable_export(t_shell *shell);
int			handle_heredoc(t_redir *redir, t_malloc **lst_malloc);
t_token		*find_pipe(t_token *tok);
int			count_args_tokens(t_token *tok);
char		**extract_args(t_token *tok);
t_redir		*extract_redirs(t_token *tok);
t_node		*build_cmd(t_token *tok);
t_node		*tokens_to_ast(t_token *tok);
void		add_redir_back(t_redir **head, t_redir *new);
void		apply_redirections(t_redir *redir, t_shell *shell);
//void	clean_argv_redirs(t_node *node);
int	count_args(char **args);
//int is_redir_token(char *s);

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

t_token		*create_token(char *word, int type, t_malloc **lst_malloc,
				t_token **token_lst);
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
char		*remix_readline(const char *prompt, t_malloc **lst_malloc);

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
void		check_syntax(t_token **lst_token, const char *prompt, char **line,
				t_malloc **lst_malloc);

/*	pipe_error	*/

bool		check_pipe(t_token *lst_token, const char *prompt, char **line,
				t_malloc **lst_malloc);

/*	Redir error	*/

bool		consecutive_redir(t_token *lst_token, char **bad_word,
				t_malloc **lst_malloc);
bool		last_token_is_redir(t_token *lst_token);
bool		check_redir(t_token *lst_token, const char *prompt,
				t_malloc **lst_malloc);

/*	Incomplete input	*/

bool		last_char_is_pipe(char *line);
bool		is_incomplete_input(char *line);

extern int	g_signal;

#endif