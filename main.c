/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:54:47 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/26 10:42:15 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	execute_pipeline(t_node *root, t_shell *shell, t_malloc **malloc_lst)
{
	expand_tree(root, shell);
	process_heredocs(root, shell, malloc_lst);
	execute_node(root, shell, malloc_lst);
	close_heredocs(root);
	clean_node(root);
}

static void	process_command(char *line, t_shell *shell, t_malloc **malloc_lst)
{
	t_cmd	*cmd_list;
	t_node	*root;

	if (is_only_space(line))
		return ;
	add_history(line);
	cmd_list = parse_input(line, malloc_lst);
	if (!cmd_list)
		return ;
	root = cmd_list_to_ast(cmd_list);
	if (!root)
		return ;
	execute_pipeline(root, shell, malloc_lst);
}

void	run_interactive(t_shell *shell, t_malloc **malloc_lst)
{
	char	*line;
	t_cmd	*cmd_list;
	t_node	*root;

	while (1)
	{
		clean_lst_malloc(malloc_lst);
		if (!read_prompt(&line, malloc_lst))
		{
			printf("exit\n");
			break ;
		}
		if (g_signal == SIGINT)
		{
			shell->last_status = 130;
			g_signal = 0;
		}
		process_command(line, shell, malloc_lst);
		if (shell->should_exit)
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_malloc	*malloc_lst;

	init_shell_maloc_lst(&malloc_lst, &shell, envp);
	gestionnaire_signaux();
	bypass_ac_av(&argc, argv, &shell);
	run_interactive(&shell, &malloc_lst);
	if (g_signal == SIGINT)
	{
		shell.last_status = 130;
		g_signal = 0;
	}
	clean_lst_malloc(&malloc_lst);
	clean_history_malloc_shell(&shell, &malloc_lst);
	return (shell.last_status);
}
