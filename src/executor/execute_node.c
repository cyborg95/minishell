/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:49:57 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/21 11:02:33 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_node(t_node *node, t_shell *shell, t_malloc **malloc_lst)
{
	if (!node)
		return (shell->last_status);
	if (node->type == NODE_PIPE)
		shell->last_status = execute_pipe(node, shell, malloc_lst);
	else
		shell->last_status = execute_command(node, shell, malloc_lst);
	return (shell->last_status);
}
