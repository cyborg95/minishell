/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 07:50:57 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/13 07:51:14 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	====================================================	*/

bool	check_pipe(t_token *lst_token, const char *prompt,
	char **line, t_malloc **lst_malloc)
{
	if (is_pipe_first (lst_token) || operator_after_pipe (lst_token))
	{
		printf ("%ssyntax error near unexpected token `|'\n", prompt);
		return (false);
	}
	else if (is_pipe_last (lst_token))
	{
		if (should_multiligne_pipe (lst_token))
			handle_multiligne_case (line, lst_malloc);
		else
		{
			printf ("%ssyntax error near unexpected token `|'\n", prompt);
			return (false);
		}
	}
	return (true);
}

/*	====================================================	*/