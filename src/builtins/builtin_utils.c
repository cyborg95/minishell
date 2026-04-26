/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:21:55 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/26 10:11:04 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stddef.h>
#include <stdio.h>

int	ft_1strcmp(const char *s1, const char *s2)
{
	size_t	in;

	in = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[in] && s2[in])
	{
		if ((unsigned char)s1[in] != (unsigned char)s2[in])
			return ((unsigned char)s1[in] - (unsigned char)s2[in]);
		in++;
	}
	return ((unsigned char)s1[in] - (unsigned char)s2[in]);
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_1strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_1strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_1strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_1strcmp(cmd, "export") == 0)
		return (1);
	if (ft_1strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_1strcmp(cmd, "env") == 0)
		return (1);
	if (ft_1strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

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

static int	execute_builtin2(t_node *node, t_shell *shell, t_exec_ctx *ctx)

{
	if (ft_1strcmp(node->argv[0], "export") == 0)
		shell->last_status = exec_with_redir(node, shell, export_wrapper, ctx);
	else if (ft_1strcmp(node->argv[0], "unset") == 0)
		shell->last_status = exec_with_redir(node, shell, unset_wrapper, ctx);
	else if (ft_1strcmp(node->argv[0], "exit") == 0)
		shell->last_status = exec_with_redir(node, shell, exit_wrapper, ctx);
	else
		return (0);
	return (shell->last_status);
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
	{
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
		return (shell->last_status);
	}
	status = builtin(arg);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	return (status);
}

int	execute_builtin(t_node *node, t_shell *shell)
{
	t_exec_ctx	ctx;

	if (!node || !node->argv || !node->argv[0])
		return (0);
	ctx.argv = node->argv;
	ctx.shell = shell;
	if (ft_1strcmp(node->argv[0], "cd") == 0)
		shell->last_status = exec_with_redir(node, shell, cd_wrapper, &ctx);
	else if (ft_1strcmp(node->argv[0], "echo") == 0)
	{
		if (node->redirs)
			shell->last_status = run_builtin_in_child(node, shell,
					echo_wrapper, node->argv);
		else
			shell->last_status = echo_wrapper(node->argv);
	}
	else if (ft_1strcmp(node->argv[0], "pwd") == 0)
	{
		if (node->redirs)
			shell->last_status = run_builtin_in_child(node, shell,
					pwd_wrapper, NULL);
		else
			shell->last_status = pwd_wrapper(NULL);
	}
	else if (ft_1strcmp(node->argv[0], "env") == 0)
	{
		if (node->redirs)
			shell->last_status = run_builtin_in_child(node, shell,
					env_wrapper, shell->env);
		else
			shell->last_status = env_wrapper(shell->env);
	}
	else
		return (execute_builtin2(node, shell, &ctx));
	return (shell->last_status);
}
