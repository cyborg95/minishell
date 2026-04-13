/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:54:47 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/13 08:38:00 by wngambi          ###   ########.fr       */
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

	(void)argc;
	(void)argv;
	malloc_lst = NULL;
	shell.env = init_env(envp);
	shell.envp_array = env_list_to_array(shell.env);
	shell.last_status = 0;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (!read_prompt(&line, &malloc_lst))
			continue ;
		add_history(line);
		cmd_list = parse_input(line, &malloc_lst);
		//display_cmd (cmd_list);
		free_remix(line, &malloc_lst);
		line = NULL;
		if (!cmd_list)
		{
			clean_lst_malloc(malloc_lst);
			malloc_lst = NULL;
			continue ;
		}
		root = cmd_list_to_ast(cmd_list, &malloc_lst);
		expand_tree(root, &shell, &malloc_lst);
		process_heredocs(root, &malloc_lst);
		execute_node(root, &shell);
		clean_lst_malloc(malloc_lst);
		malloc_lst = NULL;
	}
	ft_free_tab(shell.envp_array);
	free_env_list(shell.env);
	return (rl_clear_history(), shell.last_status);
}
