/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:05:02 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/21 11:02:33 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_stdout_redir(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == R_OUT || redirs->type == R_APPEND)
			return (1);
		redirs = redirs->next;
	}
	return (0);
}

int	has_stdin_redir(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == R_IN || redirs->type == R_HEREDOC)
			return (1);
		redirs = redirs->next;
	}
	return (0);
}

static void	exec_pid_left(t_node *node, t_shell *shell, int fd[2],
		t_malloc **malloc_lst)
{
	if (!has_stdout_redir(node->left->redirs))
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	apply_redirections(node->left->redirs, shell);
	execute_node(node->left, shell, malloc_lst);
	if (malloc_lst)
		clean_lst_malloc(malloc_lst);
	clean_node(node);
	clean_shell(shell);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(shell->last_status);
}

static void	exec_pid_right(t_node *node, t_shell *shell, int fd[2],
		t_malloc **malloc_lst)
{
	if (!has_stdin_redir(node->right->redirs))
		dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	apply_redirections(node->right->redirs, shell);
	execute_node(node->right, shell, malloc_lst);
	if (malloc_lst)
		clean_lst_malloc(malloc_lst);
	clean_node(node);
	clean_shell(shell);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(shell->last_status);
}

int	execute_pipe(t_node *node, t_shell *shell, t_malloc **malloc_lst)
{
	int		fd[2];
	int		status;
	pid_t	pid_left;
	pid_t	pid_right;

	if (!node || !node->left || !node->right)
		return (execute_command(node->left, shell, malloc_lst));
	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	pid_left = fork();
	if (pid_left < 0)
		return (perror("fork"), 1);
	if (pid_left == 0)
		exec_pid_left(node, shell, fd, malloc_lst);
	pid_right = fork();
	if (pid_right < 0)
		return (perror("fork"), 1);
	if (pid_right == 0)
		exec_pid_right(node, shell, fd, malloc_lst);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	shell->last_status = WEXITSTATUS(status);
	return (shell->last_status);
}
