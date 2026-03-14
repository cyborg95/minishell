/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:27:42 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/14 14:52:18 by wngambi          ###   ########.fr       */
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


#endif