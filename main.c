/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:54:47 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/24 17:47:07 by otidahoh         ###   ########.fr       */
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
		if (is_only_space(line))
			continue ;
		add_history(line);
		cmd_list = parse_input(line, malloc_lst);
		if (!cmd_list)
			continue ;
		root = cmd_list_to_ast(cmd_list);
		if (!root)
			continue ;
		execute_pipeline(root, shell, malloc_lst);
		if (shell->should_exit)
			break ;
	}
}

int	run_cmd_mode(t_shell *shell, t_malloc **malloc_lst)
{
	t_cmd	*cmd_list;
	t_node	*root;

	cmd_list = parse_input(shell->cmd_from_args, malloc_lst);
	if (cmd_list)
	{
		root = cmd_list_to_ast(cmd_list);
		if (root)
			execute_pipeline(root, shell, malloc_lst);
	}
	clean_lst_malloc(malloc_lst);
	clean_shell(shell);
	return (shell->last_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_malloc	*malloc_lst;

	init_shell_maloc_lst(&malloc_lst, &shell, envp);
	gestionnaire_signaux();
	bypass_ac_av(&argc, argv, &shell);
	if (!shell.is_interactive)
		return (run_cmd_mode(&shell, &malloc_lst));
	run_interactive(&shell, &malloc_lst);
	clean_lst_malloc(&malloc_lst);
	clean_history_malloc_shell(&shell, &malloc_lst);
	return (shell.last_status);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	char		*line;
	t_cmd		*cmd_list;
	t_node		*root;
	t_malloc	*malloc_lst;

	init_shell_maloc_lst(&malloc_lst, &shell, envp);
	gestionnaire_signaux();
	bypass_ac_av(&argc, argv, &shell);
	if (!shell.is_interactive)
	{
		cmd_list = parse_input(shell.cmd_from_args, &malloc_lst);
		if (cmd_list)
		{
			root = cmd_list_to_ast(cmd_list);
			if (root)
			{
				expand_tree(root, &shell);
				process_heredocs(root, &shell, &malloc_lst);
				execute_node(root, &shell, &malloc_lst);
				close_heredocs(root);
				clean_node(root);
			}
		}
		clean_lst_malloc(&malloc_lst);
		clean_shell(&shell);
		return (shell.last_status);
	}
	while (1)
	{
		clean_lst_malloc(&malloc_lst);
		if (!read_prompt(&line, &malloc_lst))
		{
			printf("exit\n");
			break ;
		}
		add_history(line);
		cmd_list = parse_input(line, &malloc_lst);
		if (!cmd_list)
			continue ;
		root = cmd_list_to_ast(cmd_list);
		if (!root)
			continue ;
		expand_tree(root, &shell);
		process_heredocs(root, &shell, &malloc_lst);
		execute_node(root, &shell, &malloc_lst);
		close_heredocs(root);
		clean_node(root);
		if (shell.should_exit)
			break ;
		clean_lst_malloc(&malloc_lst);
	}
	clean_history_malloc_shell(&shell, &malloc_lst);
	return (shell.last_status);
}*/
