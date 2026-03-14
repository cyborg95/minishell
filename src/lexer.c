/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:01:58 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/14 18:59:51 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	=====================================================	*/


// Regrouper le cas des operateurs ensmbles et le cas des cmd dans un uatre pour qu 'il y ait que deux cas 


void	lexer(t_token *lst_token, t_malloc *lst_malloc, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (line[i] == '|')
			token_pipe (lst_token, lst_malloc);
		else if (line[i] == '<')
			token_redir_in (lst_token, lst_malloc);
		else if (line[i] == '>')
			token_redir_out (lst_token, lst_malloc);
		else if (line[i] == '<<')
			token_heredoc (lst_token, lst_malloc);
		else if (line[i] == '>>')
			token_append (lst_token, lst_malloc);
		else
			token_cmd(lst_token, lst_malloc);
		i++;
	}
}

/*	=====================================================	*/

void	token_pipe(t_token *token_lst, t_malloc *lst_malloc)
{
	t_token	*token_pipe;

	if (!token_lst || !lst_malloc)
		return ;
	token_pipe = create_token (token_lst, NULL, PIPE);
	add_back_token_lst (token_lst, token_pipe);
}

/*	=====================================================	*/

void	token_redir_in(t_token *token_lst, t_malloc *lst_malloc)
{
	t_token	*token_redir_in;

	if (!token_lst || !lst_malloc)
		return ;
	token_redir_in = create_token (token_lst, NULL, REDIR_IN);
	add_back_token_lst (token_lst, token_redir_in);
}

/*	=====================================================	*/

void	token_redir_out(t_token *token_lst, t_malloc *lst_malloc)
{
	t_token	*token_redir_out;

	if (!token_lst || !lst_malloc)
		return ;
	token_redir_out = create_token (token_lst, NULL, REDIR_OUT);
	add_back_token_lst (token_lst, token_redir_out);
}

/*	=====================================================	*/

void	token_redir_herdeoc(t_token *token_lst, t_malloc *lst_malloc)
{
	t_token	*token_redir_heredoc;

	if (!token_lst || !lst_malloc)
		return ;
	token_redir_heredoc = create_token (token_lst, NULL, HEREDOC);
	add_back_token_lst (token_lst, token_redir_heredoc);
}

/*	=====================================================	*/