/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:27:42 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/15 14:39:27 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*	======	Library Used	======	*/

# include <stdbool.h>
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

typedef struct s_malloc	t_malloc;
typedef struct s_token	t_token;

struct s_malloc
{
	void		*adress_malloc;
	t_malloc	*next;
};

typedef struct s_token
{
	char			*word;
	t_type			type;
	struct s_token	*next;
}	t_token;

/*	======	Functions Definition	======	*/

/*	======	lexer.c	======	*/

void		clean_token(t_token *token_lst);
t_token		*create_token(t_token *token_lst, char *word, int type);
void		add_back_token_lst(t_token *token_lst, t_token *token);

/*	======	malloc.c	======	*/

void		clean_lst_malloc(t_malloc *lst_malloc);
t_malloc	*create_node_malloc(void *address_malloc);
void		add_malloc_in_lst(t_malloc *lst_malloc, t_malloc *malloc_node);
void		*malloc_remix(size_t nb_octets, t_malloc *lst_malloc);

/*	======	tools.c	======	*/

bool		is_space(char c);
bool		is_quote(char c);
bool		is_operator(char c);
int			ft_strlen(char *str);

#endif