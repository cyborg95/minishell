/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: w <w@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:27:42 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/16 00:58:47 by w                ###   ########.fr       */
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

#endif