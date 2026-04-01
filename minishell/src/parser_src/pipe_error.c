/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:12:16 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/26 14:43:48 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_pipe_first(t_token *lst_token)
{
	if (!lst_token)
		return (false);
	if (lst_token->type == PIPE)
		return (true);
	else
		return (false);
}

static bool	operator_after_pipe(t_token *lst_token)
{
	if (!lst_token)
		return (false);
	while (lst_token->next)
	{
		if (lst_token->type == PIPE)
		{
			if (lst_token->next->type != WORD)
				return (true);
		}
		lst_token = lst_token->next;
	}
	return (false);
}

/*	====================================================	*/

bool	check_pipe(t_token *lst_token, const char *prompt,
	char **line, t_malloc **lst_malloc)
{

	(void)line;
	(void)lst_malloc;
	if (is_pipe_first (lst_token))
	{
		printf ("%ssyntax error near unexpected token `|'\n", prompt);
		return (false);
	}
	if (operator_after_pipe (lst_token))
	{
		while (lst_token->type != PIPE && lst_token->next->type != WORD)
			lst_token = lst_token->next;
		printf ("%ssyntax error near unexpected token `%s'\n",
			prompt, lst_token->next->word);
		return (false);
	}
	return (true);
}

