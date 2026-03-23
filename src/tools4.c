/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:41:23 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/23 10:47:45 by wngambi          ###   ########.fr       */
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