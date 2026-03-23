/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:41:23 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/23 12:39:46 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	=====================================================	*/

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