/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 09:28:26 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/26 14:42:38 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Carre on revient pas dessus	*/
bool	consecutive_redir(t_token *lst_token, char **bad_word,
	t_malloc **lst_malloc)
{
	t_token	*curent_token;
	t_token	*next_token;

	if (!lst_token || !lst_token->next)
		return (false);
	curent_token = lst_token;
	while (curent_token->next != NULL)
	{
		next_token = curent_token->next;
		if (is_redir (curent_token) && (is_redir (next_token)
				|| is_pipe((next_token->word)[0])))
		{
			*bad_word = ft_strdup (next_token->word, lst_malloc);
			return (true);
		}
		curent_token = curent_token->next;
	}
	return (false);
}


/*	Carre on revient pas dessus	*/
bool	last_token_is_redir(t_token *lst_token)
{
	if (!lst_token)
		return (false);
	while (lst_token->next != NULL)
		lst_token = lst_token->next;
	if (lst_token->type == REDIR_IN)
		return (true);
	if (lst_token->type == REDIR_OUT)
		return (true);
	if (lst_token->type == HEREDOC)
		return (true);
	if (lst_token->type == APPEND)
		return (true);
	return (false);
}

/*	Carre on revient pas dessus	*/
bool	check_redir(t_token *lst_token, const char *prompt,
		t_malloc **lst_malloc)
{
	char	*bad_word;

	if (last_token_is_redir (lst_token))
	{
		printf ("%ssyntax error near unexpected token `newline'\n", prompt);
		return (false);
	}
	else if (consecutive_redir (lst_token, &bad_word, lst_malloc))
	{
		printf ("%ssyntax error near unexpected token `%s'\n",
			prompt, bad_word);
		return (false);
	}
	return (true);
}

