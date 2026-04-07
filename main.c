/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:54:47 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/03 13:25:34 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	process_heredocs(t_node *node, t_malloc **lst_malloc)
{
	t_redir	*r;

	if (!node)
		return ;
	r = node->redirs;
	while (r)
	{
		if (r->type == R_HEREDOC)
			r->fd = handle_heredoc(r, lst_malloc);
		r = r->next;
	}
	process_heredocs(node->left, lst_malloc);
	process_heredocs(node->right, lst_malloc);
}

int	handle_heredoc(t_redir *redir, t_malloc **lst_malloc)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		return (perror("pipe"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!line || ft_1strcmp(line, redir->file) == 0)
		{
			add_malloc_in_lst(lst_malloc, create_node_malloc(line));
			break ;
		}
		write(fd[1], line, ft_1strlen(line));
		write(fd[1], "\n", 1);
		add_malloc_in_lst(lst_malloc, create_node_malloc(line));
	}
	close(fd[1]);
	return (fd[0]);
}

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
