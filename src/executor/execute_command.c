/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:36:28 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/21 19:03:55 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_command(t_node *node, t_shell *shell, t_malloc **malloc_lst)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!node)
		return (shell->last_status);

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	// ✅ minimal fix
	if (node->redirs)
	{
		if (apply_redirections(node->redirs, shell) == -1)
		{
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			return (1);
		}
	}

	if (!node->argv || !node->argv[0])
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (shell->last_status);
	}
	if (is_builtin(node->argv[0]))
		shell->last_status = execute_builtin(node, shell);
	else
		execute_external(node, shell, malloc_lst);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (shell->last_status);
}
