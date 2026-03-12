/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:49:57 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/07 17:30:53 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_node(t_node *node, t_shell *shell)
{
	if (!node)
		return (shell->last_status);
	if (node->type == NODE_PIPE)
		shell->last_status = execute_pipe(node, shell);
	else
		shell->last_status = execute_command(node, shell);
	return (shell->last_status);
}
