/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:36:28 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/24 18:26:10 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	rest_fd(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static void	run_command(t_node *node, t_shell *shell, t_malloc **malloc_lst)
{
	if (is_builtin(node->argv[0]))
		shell->last_status = execute_builtin(node, shell);
	else
		execute_external(node, shell, malloc_lst);
}

int	execute_command(t_node *node, t_shell *shell, t_malloc **malloc_lst)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!node)
		return (shell->last_status);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (node->redirs)
	{
		if (apply_redirections(node->redirs, shell) == -1)
		{
			rest_fd(saved_stdin, saved_stdout);
			return (1);
		}
	}
	if (!node->argv || !node->argv[0])
	{
		rest_fd(saved_stdin, saved_stdout);
		return (shell->last_status);
	}
	run_command(node, shell, malloc_lst);
	rest_fd(saved_stdin, saved_stdout);
	return (shell->last_status);
}
