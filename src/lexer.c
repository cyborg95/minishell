/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:01:58 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/15 16:07:06 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	=====================================================	*/


// Regrouper le cas des operateurs ensmbles et le cas des cmd dans un uatre pour qu 'il y ait que deux cas 


void	lexer(t_token *lst_token, t_malloc *lst_malloc, char *line)
{
	while (*line)
	{
		
	}
}

/*	=====================================================	*/

void	token_pipe(t_token *token_lst)
{
	t_token	*token_pipe;

	if (!token_lst)
		return ;
	token_pipe = create_token (token_lst, NULL, PIPE);
	add_back_token_lst (token_lst, token_pipe);
}

/*	=====================================================	*/

void	token_redir_in(t_token *token_lst)
{
	t_token	*token_redir_in;

	if (!token_lst)
		return ;
	token_redir_in = create_token (token_lst, NULL, REDIR_IN);
	add_back_token_lst (token_lst, token_redir_in);
}

/*	=====================================================	*/

void	token_redir_out(t_token *token_lst)
{
	t_token	*token_redir_out;

	if (!token_lst)
		return ;
	token_redir_out = create_token (token_lst, NULL, REDIR_OUT);
	add_back_token_lst (token_lst, token_redir_out);
}

/*	=====================================================	*/

void	token_redir_herdeoc(t_token *token_lst)
{
	t_token	*token_redir_heredoc;

	if (!token_lst)
		return ;
	token_redir_heredoc = create_token (token_lst, NULL, HEREDOC);
	add_back_token_lst (token_lst, token_redir_heredoc);
}

/*	=====================================================	*/

void	token_operator(char *line, t_token *lst_token, t_malloc *lst_malloc)
{
	int	i;
	int	len_str;

	if (!lst_token)
		return ;
	i = 0;
	len_str = ft_strlen (line);

	if (line == '|')
		return (token_pipe (lst_token));
	if ((i + 1) < len_str)
	{
		if (line[i] == '<' && line[i + 1] == '<')
			return (token_heredoc (lst_token));
		else if (line[i] == '>' && line[i + 1] == '>')
			return (token_append (lst_token));
		else if (line[i] == '<')
			return (token_redir_in (lst_token));
		else if (line[i] == '>')
			return (token_redir_out (lst_token));
	}
	printf ("minishell> syntax error near unexpected token `newline'");
	return (clean_token (lst_token), clean_lst_malloc (lst_malloc),
		exit (2));
}