/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 11:29:16 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/25 11:29:24 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	=====================================================	*/

#include "../../includes/minishell.h"

t_cmd	*parse_input(char *line, t_malloc **lst_malloc)
{
	t_token		*token_list;
	t_cmd		*cmd_lst;

	token_list = NULL;
	cmd_lst = NULL;
	init_token_lst (&token_list, lst_malloc, &line);
	if (!check_token_lst (&token_list, PROMPT, &line, lst_malloc))
		return (NULL);
	init_command_lst (token_list, lst_malloc, &cmd_lst);
	free_token_lst (&token_list, lst_malloc);
	return (cmd_lst);
}

/*	=====================================================	*/