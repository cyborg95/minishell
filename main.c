/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:54:47 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/20 12:00:15 by wngambi          ###   ########.fr       */
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
	gestionnaire_signaux ();
	init_shell_maloc_lst (&malloc_lst, &shell, envp);

	/* Ma liste de malloc doit contneur uniquement:
		- Line
		- Liste de commande
		- AST
		- Token
		- Expand
	*/
	while (1)
	{
		if (!read_prompt(&line, &malloc_lst))
		{
			clean_lst_malloc (&malloc_lst);
			continue ;
		}
		add_history(line);
		cmd_list = parse_input(line, &malloc_lst);
		if (!cmd_list)
		{
			clean_lst_malloc (&malloc_lst);
			continue ;
		}
		root = cmd_list_to_ast(cmd_list);
		/*	STOP LIST MALLOC */
		expand_tree(root, &shell);
		process_heredocs(root, &shell, &malloc_lst);
		execute_node(root, &shell);
		/*	Nettoyage 	*/
		close_heredocs(root);
		clean_node (root);
		clean_lst_malloc (&malloc_lst);
	}
	clean_history_malloc_shell (&shell, &malloc_lst);
	return (shell.last_status);
}
//display_cmd (cmd_list);