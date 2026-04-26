/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 11:35:00 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/26 10:31:49 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_builtin_child(pid_t pid, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		shell->last_status = 128 + WTERMSIG(status);
		return (shell->last_status);
	}
	shell->last_status = WEXITSTATUS(status);
	return (shell->last_status);
}

static int	run_builtin_in_child(t_node *node, t_shell *shell,
		int (*builtin)(void *), void *arg)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		if (apply_redirections(node->redirs, shell) == -1)
			exit(1);
		exit(builtin(arg));
	}
	return (wait_builtin_child(pid, shell));
}

int	run_builtin_cmd(t_node *node, t_shell *shell,
		int (*builtin)(void *), void *arg)
{
	if (node->redirs)
		return (run_builtin_in_child(node, shell, builtin, arg));
	return (builtin(arg));
}

static int	restore_stdio(int saved_stdout, int saved_stdin, int status)
{
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	return (status);
}

int	exec_with_redir(t_node *node, t_shell *shell,
		int (*builtin)(void *), void *arg)
{
	int	saved_stdout;
	int	saved_stdin;
	int	status;

	if (!node->redirs)
		return (builtin(arg));
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdout == -1 || saved_stdin == -1)
	{
		if (saved_stdout != -1)
			close(saved_stdout);
		if (saved_stdin != -1)
			close(saved_stdin);
		return (1);
	}
	if (apply_redirections(node->redirs, shell) == -1)
		return (restore_stdio(saved_stdout, saved_stdin, shell->last_status));
	status = builtin(arg);
	return (restore_stdio(saved_stdout, saved_stdin, status));
}
