/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:33:07 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/23 18:40:26 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_exit(t_node *node, t_shell *shell,
		t_malloc **malloc_lst, int code)
{
	perror(node->argv[0]);
	if (malloc_lst)
		clean_lst_malloc(malloc_lst);
	clean_node(node);
	clean_shell(shell);
	exit(code);
}

static int	handle_no_path(t_node *node, t_shell *shell)
{
	shell->last_status = 127;
	if (ft_strchr(node->argv[0], '/'))
		printf("minishell: %s: No such file or directory\n", node->argv[0]);
	else
		printf("minishell: %s: command not found\n", node->argv[0]);
	return (127);
}

static void	handle_parent(t_node *node, t_shell *shell)
{
	int	sig;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(node->pid, &node->status, 0);
	if (WIFSIGNALED(node->status))
	{
		sig = WTERMSIG(node->status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
		shell->last_status = 128 + sig;
	}
	else
		shell->last_status = WEXITSTATUS(node->status);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

int	execute_external(t_node *node, t_shell *shell, t_malloc **malloc_lst)
{
	if (!node || !node->argv || !node->argv[0])
		return (1);
	if (!shell->envp_array)
		shell->envp_array = env_list_to_array(shell->env);
	node->path = path_finder(node->argv[0], shell->env);
	if (!node->path)
		return (handle_no_path(node, shell));
	node->pid = fork();
	if (node->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		apply_redirections(node->redirs, shell);
		execve(node->path, node->argv, shell->envp_array);
		if (errno == ENOENT)
			child_exit(node, shell, malloc_lst, 127);
		else if (errno == EACCES)
			child_exit(node, shell, malloc_lst, 126);
		else
			child_exit(node, shell, malloc_lst, 1);
	}
	handle_parent(node, shell);
	return (shell->last_status);
}
