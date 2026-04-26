/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:36:28 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/26 10:11:04 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	run_command(t_node *node, t_shell *shell, t_malloc **malloc_lst)
{
	if (is_builtin(node->argv[0]))
		shell->last_status = execute_builtin(node, shell);
	else
		execute_external(node, shell, malloc_lst);
}

int	execute_command(t_node *node, t_shell *shell, t_malloc **malloc_lst)
{
	if (!node)
		return (shell->last_status);
	if (!node->argv || !node->argv[0])
		return (shell->last_status);
	run_command(node, shell, malloc_lst);
	return (shell->last_status);
}
