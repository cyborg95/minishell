/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:28:38 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/14 18:49:23 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	=====================================================	*/

void	token_append(t_token *token_lst, t_malloc *lst_malloc)
{
	t_token	*token_append;

	if (!token_lst || !lst_malloc)
		return ;
	token_append = create_token (token_lst, NULL, APPEND);
	add_back_token_lst (token_lst, token_append);
}

/*	=====================================================	*/

void	token_cmd(t_token *token_lst, t_malloc *lst_malloc, int *i, char **line)
{
	t_token	*token_cmd;
	int		j;
	bool	quote_flag;

	if (!token_lst || !lst_malloc)
		return ;
	j = *i;
	while (line[j])
	{
		if (is_space && quote_flag)
			j++;
	}



	
	token_append = create_token (token_lst, NULL, APPEND);
	add_back_token_lst (token_lst, token_append);
}

/*	=====================================================	*/



