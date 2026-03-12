/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:36:28 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/07 17:31:29 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_command(t_node *node, t_shell *shell)
{
	if (!node || !node->argv || !node->argv[0])
		return (shell->last_status);
	if (is_builtin(node->argv[0]))
		shell->last_status = execute_builtin(node, shell);
	else
		execute_external(node, shell);
	return (shell->last_status);
}
