/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:54:47 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/27 12:27:16 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	*trim_filename(char *s)
{
	int	len;

	if (!s)
		return (NULL);
	len = ft_1strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == ' '))
		s[--len] = '\0';
	return (s);
}

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
	int			fd[2];
	char		*line;

	if (pipe(fd) < 0)
		return (perror("pipe"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_1strcmp(line, redir->file) == 0)
		{
			add_malloc_in_lst(lst_malloc, create_node_malloc(line));
			break ;
		}
		add_malloc_in_lst(lst_malloc, create_node_malloc(line));
		write(fd[1], line, ft_1strlen(line));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	return (fd[0]);
}

void	add_redir_back(t_redir **head, t_redir *new)
{
	t_redir	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
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
	t_shell		shell;
	char		*line;
	t_node		*root;
	t_token		*tokens;
	t_malloc	*malloc_lst;

	rl_catch_signals = 0;
	((void)argc, (void)argv);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	shell.env = init_env(envp);
	shell.envp_array = env_list_to_array(shell.env);
	shell.last_status = 0;
	while (1)
	{
		malloc_lst = NULL;
		line = readline("minishell$ ");
		add_malloc_in_lst(&malloc_lst, create_node_malloc(line));
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		add_history(line);
		tokens = NULL;
		lexer(&tokens, &malloc_lst, &line);
		check_syntax(&tokens, PROMPT, &line, &malloc_lst);
		if (!tokens)
		{
			clean_lst_malloc(malloc_lst);
			continue ;
		}
		root = tokens_to_ast(tokens);
		tokens = NULL;
		if (!root)
		{
			clean_lst_malloc(malloc_lst);
			malloc_lst = NULL;
			continue ;
		}
		expand_tree(root, &shell);
		process_heredocs(root, &malloc_lst);
		execute_node(root, &shell);
		free_node(root);
		clean_lst_malloc(malloc_lst);
	}
	(ft_free_tab(shell.envp_array), free_env_list(shell.env));
	return (rl_clear_history(), shell.last_status);
}
