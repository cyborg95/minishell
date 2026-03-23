/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 09:28:26 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/23 09:36:32 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	last_token_is_redir(t_token *lst_token, const char *prompt)
{
	if (!lst_token)
		return (false);
	while (lst_token->next != NULL)
		lst_token = lst_token->next;
	if ((lst_token->type == REDIR_IN))
		return (true);
	if ((lst_token->type == REDIR_OUT))
		return (true);
	if ((lst_token->type == HEREDOC))
		return (true);
	if ((lst_token->type == APPEND))
		return (true);
}