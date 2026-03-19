/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:28:38 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/19 12:16:37 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	=====================================================	*/

void	token_redir_out(t_token **token_lst, t_malloc **lst_malloc)
{
	t_token	*token_redir_out;

	if (!token_lst || !lst_malloc)
		return ;
	token_redir_out = create_token (NULL, REDIR_OUT, lst_malloc, token_lst);
}

/*	=====================================================	*/

void	token_redir_heredoc(t_token **token_lst, t_malloc **lst_malloc)
{
	t_token	*token_redir_heredoc;

	if (!token_lst || !lst_malloc)
		return ;
	token_redir_heredoc = create_token (NULL, HEREDOC, lst_malloc, token_lst);
}

/*	=====================================================	*/

void	token_operator(char *line, t_token **lst_token, t_malloc **lst_malloc)
{
	if (!lst_token || !lst_malloc)
		return ;
	if (*line == '|')
		return (token_pipe (lst_token, lst_malloc));
	if (*(line + 1) != '\0')
	{
		if (*line == '<' && *(line + 1) == '<')
			return (token_redir_heredoc (lst_token, lst_malloc));
		else if (*line == '>' && *(line + 1) == '>')
			return (token_append (lst_token, lst_malloc));
		else if (*line == '<')
			return (token_redir_in (lst_token, lst_malloc));
		else if (*line == '>')
			return (token_redir_out (lst_token, lst_malloc));
	}
	printf ("minishell> syntax error near unexpected token `newline'");
	return (clean_token (lst_token), clean_lst_malloc (*lst_malloc),
		exit (2));
}

/*	=====================================================	*/

void	token_append(t_token **token_lst, t_malloc **lst_malloc)
{
	t_token	*token_append;

	if (!token_lst || !lst_malloc)
		return ;
	token_append = create_token (NULL, APPEND, lst_malloc, token_lst);
}

/*	=====================================================	*/