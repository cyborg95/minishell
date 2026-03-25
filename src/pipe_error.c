/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: w <w@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:12:16 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/25 13:09:24 by w                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static bool	is_pipe_first(t_token *lst_token)
{
	if (!lst_token)
		return (false);
	if (lst_token->type == PIPE)
		return (true);
	else
		return (false);
}

/*	====================================================	*/
/*
static bool	is_pipe_last(t_token *lst_token)
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
*/
/*	====================================================	*/

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


/*	====================================================	*/
