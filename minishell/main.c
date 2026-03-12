/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:54:47 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/11 16:44:03 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_node	*parse_line(char *line)
{
	char	**pipes;
	t_node	*node;

	pipes = ft_split(line, '|');
	if (!pipes)
		return (NULL);
	if (!pipes[1])
	{
		node = malloc(sizeof(t_node));
		node->type = NODE_CMD;
		node->argv = ft_split(pipes[0], ' ');
		node->left = NULL;
		node->right = NULL;
		node->redirs = NULL;
	}
	else
	{
		node = malloc(sizeof(t_node));
		node->type = NODE_PIPE;
		node->left = parse_line(pipes[0]);
		node->right = parse_line(pipes[1]);
		node->argv = NULL;
		node->redirs = NULL;
	}
	return (ft_free_tab(pipes), node);
}

void	free_node(t_node *node)
{
	int	i;

	if (!node)
		return ;
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
			free(node->argv[i++]);
		free(node->argv);
	}
	free_node(node->left);
	free_node(node->right);
	free(node);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;
	t_node	*root;

	((void)argc, (void)argv);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	shell.env = init_env(envp);
	shell.envp_array = env_list_to_array(shell.env);
	shell.last_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		add_history(line);
		root = parse_line(line);
		(expand_tree(root, &shell), execute_node(root, &shell));
		(free_node(root), free(line));
	}
	(ft_free_tab(shell.envp_array), free_env_list(shell.env));
	return (rl_clear_history(), shell.last_status);
}
