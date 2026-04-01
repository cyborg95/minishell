/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: w <w@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:49:04 by w                 #+#    #+#             */
/*   Updated: 2026/03/25 18:50:33 by w                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	=====================================================	*/

void	token_pipe(t_token **token_lst, t_malloc **lst_malloc)
{
	if (!token_lst || !lst_malloc)
		return ;
	create_token (ft_strdup ("|", lst_malloc), PIPE, lst_malloc, token_lst);
}

/*	=====================================================	*/

void	token_redir_in(t_token **token_lst, t_malloc **lst_malloc)
{
	if (!token_lst)
		return ;
	create_token (ft_strdup ("<", lst_malloc), REDIR_IN, lst_malloc, token_lst);
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
bool	are_quotes_closed(char *line)
{
	bool	squote;
	bool	dquote;

	squote = false;
	dquote = false;
	if (!line && !(*line))
		return (false);
	while (*line)
	{
		if (is_quote (*line))
		{
			if (is_single_quote (*line) && dquote == false)
				squote = !squote;
			else if (is_double_quote(*line) && squote == false)
				dquote = !dquote;
		}
		line++;
	}
	if (squote == false && dquote == false)
		return (true);
	return (false);
}

/*	=====================================================	*/