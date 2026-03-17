/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:27:42 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/17 12:22:17 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*	======	Library Used	======	*/

# include <stdbool.h>
# include <stdlib.h>
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

/*	======	Fonction Used	======	*/

	/*	Lexing Functions	*/

void		lexer(t_token **lst_token, t_malloc **lst_malloc, char *line);
void		token_pipe(t_token **token_lst, t_malloc **lst_malloc);
void		token_redir_in(t_token **token_lst, t_malloc **lst_malloc);
void		token_redir_out(t_token **token_lst, t_malloc **lst_malloc);
void		token_redir_heredeoc(t_token **token_lst, t_malloc **lst_malloc);
void		token_operator(char *line, t_token **lst_token,
				t_malloc **lst_malloc);
void		token_append(t_token **token_lst, t_malloc **lst_malloc);

	/*	Malloc Functions	*/

void		clean_lst_malloc(t_malloc *lst_malloc);
t_malloc	*create_node_malloc(void *address_malloc);
void		add_malloc_in_lst(t_malloc **lst_malloc, t_malloc *malloc_node);
void		*malloc_remix(size_t nb_octets, t_malloc **lst_malloc);

	/*	Token Functions		*/

void		clean_token(t_token **token_lst);
t_token		*create_token(char *word, int type,
				t_malloc **lst_malloc, t_token **token_lst);
void		add_back_token_lst(t_token **token_lst, t_token *token);
void		display_token(t_token *token_lst);

	/*	Token Functions		*/

bool		is_space(char c);
bool		is_quote(char c);
bool		is_operator(char c);
int			ft_strlen(char *str);


#endif