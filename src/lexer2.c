/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:28:38 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/15 16:01:32 by wngambi          ###   ########.fr       */
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

/*	=====================================================	*/



