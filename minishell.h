/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:27:42 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/12 15:57:16 by wngambi          ###   ########.fr       */
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

typedef struct s_token
{
	char			*word;
	t_type			type;
	struct s_token	*next;
}	t_token;




#endif