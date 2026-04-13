/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:44:15 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/13 08:13:04 by wngambi          ###   ########.fr       */
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

t_env			*init_env(char **envp);
char			**env_list_to_array(t_env *env);
void			ft_free_tab(char **tab);
void			free_env_list(t_env *env);
int				ft_1strcmp(const char *s1, const char *s2);
void			add_or_update_env(t_shell *shell, char *key, char *value);
char			*my_getenv(char *name, char **env);
void			handle_signal(int sig);
char			*expand_var(char *arg, t_shell *shell, t_malloc **malloc_lst);
void			expand_tree(t_node *node, t_shell *shell,
					t_malloc **malloc_lst);
int				is_valid_identifier(char *str);
int				printable_export(t_shell *shell);
int				handle_heredoc(t_redir *redir, t_malloc **lst_malloc);
char			*ft_itoa_remix(int n, t_malloc **malloc_lst);
void			free_remix(void *ptr, t_malloc **malloc_lst);
char			*get_env_value(t_env *env, char *key);

t_redir_type	convert_redir_type(int type);
t_redir			*convert_redirs(t_redir *src, t_malloc **malloc_lst);
t_node			*cmd_to_node(t_cmd *cmd, t_malloc **malloc_lst);
t_node			*cmd_list_to_ast(t_cmd *cmd, t_malloc **malloc_lst);

/* PARSING_MINISHELL */

void			init_command_lst(t_token *token_lst, t_malloc **malloc_lst,
					t_cmd **cmd_lst);
void			init_token_lst(t_token **token_lst, t_malloc **malloc_lst,
					char **line);
bool			read_prompt(char **line, t_malloc **malloc_lst);
t_cmd			*parse_input(char *line, t_malloc **lst_malloc);

/* COMMAND */

t_cmd			*create_cmd(t_malloc **lst_malloc, t_token *lst_token);
void			fill_cmd(t_token **lst_token, t_cmd *cmd,
					t_malloc **lst_malloc);
void			add_back_cmd(t_cmd **lst_cmd, t_cmd *cmd,
					t_malloc **lst_malloc);
void			display_cmd(t_cmd *cmd_lst);

/* ERROR */
bool			is_empty_list(t_token *lst_token);
bool			check_token_lst(t_token **lst_token, const char *prompt,
					char **line, t_malloc **lst_malloc);
/* LEXER */

void			handle_multiligne_case(char **line, t_malloc **lst_malloc);
void			back_slash_case(char **line, char *word);
char			*extract_word(char **line, char *word);

void			lexer(t_token **lst_token, t_malloc **lst_malloc, char **line);
void			token_pipe(t_token **token_lst, t_malloc **lst_malloc);
void			token_redir_in(t_token **token_lst, t_malloc **lst_malloc);
bool			are_quotes_closed(char *line);
void			token_redir_out(t_token **token_lst, t_malloc **lst_malloc);
void			handle_redir_case(char **line, t_token **lst_token,
					t_malloc **lst_malloc);
void			token_operator(char **line, t_token **lst_token,
					t_malloc **lst_malloc);
void			token_append(t_token **token_lst, t_malloc **lst_malloc);
void			init_value(bool *in_squote, bool *in_dquote, int *i);

/* MALLOC */

void			clean_lst_malloc(t_malloc *lst_malloc);
t_malloc		*create_node_malloc(void *address_malloc);
void			add_malloc_in_lst(t_malloc **lst_malloc, t_malloc *malloc_node);
void			*malloc_remix(size_t nb_octets, t_malloc **lst_malloc);
void			display_lst_malloc(t_malloc *lst_malloc);

/* PIPE ERROR */

bool			is_pipe_first(t_token *lst_token);
bool			is_pipe_last(t_token *lst_token);
bool			operator_after_pipe(t_token *lst_token);
bool			should_multiligne_pipe(t_token *lst_token);
bool			consecutive_pipe(t_token *lst_token);
bool			check_pipe(t_token *lst_token, const char *prompt, char **line,
					t_malloc **lst_malloc);

/* REDIR ERROR */

bool			consecutive_redir(t_token *lst_token, char **bad_word,
					t_malloc **lst_malloc);
bool			last_token_is_redir(t_token *lst_token);
bool			check_redir(t_token *lst_token, const char *prompt,
					t_malloc **lst_malloc);

/* REDIR */

void			handle_redir(t_malloc **lst_malloc, t_token **lst_token,
					t_cmd *cmd);
t_redir			*create_redir(t_malloc **lst_malloc, int token_type);
void			add_back_redir(t_cmd *cmd, t_redir *new_redir);
void			display_redir(t_cmd *cmd);

/* TOKEN */

t_token			*create_token(char *word, int type, t_malloc **lst_malloc,
					t_token **token_lst);
void			display_token(t_token *token_lst);

/* TOOLS */

bool			is_space(char c);
bool			is_quote(char c);
bool			is_single_quote(char c);
bool			is_double_quote(char c);
bool			is_operator(char c);

/*		Tools	2	*/

int				ft_strlen(char *str);
char			*ft_strdup(char *str, t_malloc **lst_malloc);
char			*ft_strjoin(char *line, char *new_line, t_malloc **lst_malloc);
bool			ft_strcmp(char *s1, char *s2);
char			*remix_readline(const char *prompt, t_malloc **lst_malloc);
bool			is_back_slash(char c);
bool			ends_with_backslash(char *line);
bool			is_pipe(char c);
bool			is_redir_in(char c);
bool			is_redir_out(char c);

/*		Tools	4	*/

bool			is_here_doc(char **line);
bool			is_append(char **line);
bool			is_redir(t_token *lst_token);
void			ft_bzero(void *s, size_t n);
void			display_args(char **args);
bool			end_with_pipe(char *line);
bool			is_operator_before(char *line);

/*		MERGER	*/

t_redir_type	convert_redir_type(int type);
t_redir			*convert_redirs(t_redir *src, t_malloc **malloc_lst);
t_node			*cmd_to_node(t_cmd *cmd, t_malloc **malloc_lst);
t_node			*cmd_list_to_ast(t_cmd *cmd, t_malloc **malloc_lst);

extern int		g_signal;

#endif