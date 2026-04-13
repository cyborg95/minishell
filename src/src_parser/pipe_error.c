/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:12:16 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/13 08:06:13 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	Checker les pipes	

	Si le pipe est au debut == CARRE
	SI on envoi un pipe seul apres un premier mot valide ==  CARRE
	Si le pipe est a la fin on doit faire un multiligne	== CARRE
	Si il y'a deux pipes consecutifs == CARRE
	SI le pipe n est pas suvi d un token WORD on coupe == EN COURS
	SI le pipe est a la fin de la ligne il faut que ce qui 
	suit soit bien integre au token == EN COURS
*/

/*	====================================================	*/

bool	is_pipe_first(t_token *lst_token)
{
	if (!lst_token)
		return (false);
	if (lst_token->type == PIPE)
		return (true);
	else
		return (false);
}

/*	====================================================	*/

bool	is_pipe_last(t_token *lst_token)
{
	if (!lst_token)
		return (false);
	while (lst_token->next != NULL)
		lst_token = lst_token->next;
	if (lst_token->type == PIPE)
		return (true);
	else
		return (false);
}

/*	====================================================	*/

bool	operator_after_pipe(t_token *lst_token)
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

bool	should_multiligne_pipe(t_token *lst_token)
{
	t_token	*last;
	t_token	*prev;

	if (!lst_token)
		return (false);
	last = lst_token;
	prev = NULL;
	while (last->next != NULL)
	{
		prev = last;
		last = last->next;
	}
	if (is_redir(prev))
		return (false);
	else
		return (true);
}

bool	consecutive_pipe(t_token *lst_token)
{
	if (!lst_token)
		return (false);
	while (lst_token->next)
	{
		if (lst_token->type == PIPE && lst_token->next->type == PIPE)
			return (true);
		lst_token = lst_token->next;
	}
	return (false);
}

/*	====================================================	*/