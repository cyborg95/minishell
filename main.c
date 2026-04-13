/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:54:47 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/13 11:48:15 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	char		*line;
	t_cmd		*cmd_list;
	t_node		*root;
	t_malloc	*malloc_lst;

	bypass_ac_av (&argc, argv);
	init_shell_maloc_lst (&malloc_lst, &shell, envp);
	gestionnaire_signaux ();
	while (1)
	{
		if (!read_prompt(&line, &malloc_lst))
			continue ;
		add_history(line);
		cmd_list = parse_input(line, &malloc_lst);
		if (!cmd_list)
			continue ;
		root = cmd_list_to_ast(cmd_list, &malloc_lst);
		expand_tree(root, &shell, &malloc_lst);
		process_heredocs(root, &malloc_lst);
		execute_node(root, &shell);
		clean_lst_malloc (malloc_lst);
	}
	clean_history_malloc_shell (&shell, malloc_lst);
	return (shell.last_status);
}
//display_cmd (cmd_list);