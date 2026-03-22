/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:23:29 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/22 17:35:56 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	====================================================	*/

bool	is_empty_list(t_token *lst_token)
{
	if (!lst_token)
		return (true);
	else
		return (false);
}

/*	====================================================	*/

void	check_syntax(t_token **lst_token, const char *prompt,
        char **line, t_malloc **lst_malloc)
{
	if (is_empty_list (*lst_token))
		return ;
	else if (!check_pipe (*lst_token, prompt, line, lst_malloc))
		*lst_token = NULL;
}

/*	====================================================	*/