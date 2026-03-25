/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: w <w@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:41:23 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/25 18:41:01 by w                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
bool	is_here_doc(char **line)
{
	if (!line)
		return (false);
	else
	{
		if (*(*line + 1) != '\0' && !is_redir_in (*(*line + 1)))
			return (false);
		else if (*(*line + 1) != '\0' && is_redir_in (*(*line + 1)))
			return (true);
	}
	return (false);
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
bool	is_append(char **line)
{
	if (!line)
		return (false);
	else
	{
		if (*(*line + 1) != '\0' && !is_redir_out (*(*line + 1)))
			return (false);
		else if (*(*line + 1) != '\0' && is_redir_out (*(*line + 1)))
			return (true);
	}
	return (false);
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
bool	is_redir(t_token *lst_token)
{
	if (!lst_token)
		return (false);
	else
	{
		if (lst_token->type == REDIR_IN
			|| lst_token->type == REDIR_OUT
			|| lst_token->type == HEREDOC
			|| lst_token->type == APPEND)
			return (true);
		else
			return (false);
	}
}

/*	=====================================================	*/