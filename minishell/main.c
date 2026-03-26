/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:54:47 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/26 12:46:02 by otidahoh         ###   ########.fr       */
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

/*char	**clean_args(char **args)
{
	char	**new;
	int		i;
	int		j;
	int		size;

	size = count_args(args);
	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	while (args[i])
	{
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>")
			|| !ft_strcmp(args[i], "<") || !ft_strcmp(args[i], "<<"))
			i += 2;
		else
		{
			new[j] = ft_strdup(args[i]);
			j++;
			i++;
		}
	}
	new[j] = NULL;
	return (new);
}*/

char	*trim_filename(char *s)
{
	int	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == ' '))
		s[--len] = '\0';
	return (s);
}

void	process_heredocs(t_node *node)
{
	t_redir	*r;

	if (!node)
		return ;
	r = node->redirs;
	while (r)
	{
		if (r->type == R_HEREDOC)
			r->fd = handle_heredoc(r);
		r = r->next;
	}
	process_heredocs(node->left);
	process_heredocs(node->right);
}

int	handle_heredoc(t_redir *redir)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		return (perror("pipe"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
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

/*t_redir	*parse_redirections(char **args, int *error)
{
	t_redir	*head;
	t_redir	*new;
	char	*tmp;
	int		i;

	head = NULL;
	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>")
			|| !ft_strcmp(args[i], "<") || !ft_strcmp(args[i], "<<"))
		{
			if (!args[i + 1])
			{
				printf("syntax error: missing filename\n");
				*error = 1;
				return (NULL);
			}
			new = malloc(sizeof(t_redir));
			if (!new)
				return (NULL);
			new->next = NULL;
			if (!ft_strcmp(args[i], ">"))
				new->type = R_OUT;
			else if (!ft_strcmp(args[i], ">>"))
				new->type = R_APPEND;
			else if (!ft_strcmp(args[i], "<"))
				new->type = R_IN;
			else
				new->type = R_HEREDOC;
			tmp = ft_strdup(args[i + 1]);
			if (!tmp)
				return (NULL);
			new->file = trim_filename(tmp);
			add_redir_back(&head, new);
			i += 2;
		}
		else
			i++;
	}
	return (head);
}

t_node	*parse_line(char *line)
{
	char	**pipes;
	t_node	*node;
	char	**args;
	int		error;

	error = 0;
	pipes = ft_split(line, '|');
	if (!pipes)
		return (NULL);
	node = malloc(sizeof(t_node));
	if (!node)
		return (ft_free_tab(pipes), NULL);
	if (!pipes[1])
	{
		node->type = NODE_CMD;
		args = ft_split(pipes[0], ' ');
		if (!args)
			return (ft_free_tab(pipes), free(node), NULL);
		node->redirs = parse_redirections(args, &error);
		if (error)
		{
			ft_free_tab(args);
			ft_free_tab(pipes);
			free(node);
			return (NULL);
		}
		node->argv = clean_args(args);
		node->left = NULL;
		node->right = NULL;
		ft_free_tab(args);
	}
	else
	{
		node->type = NODE_PIPE;
		node->left = parse_line(pipes[0]);
		node->right = parse_line(pipes[1]);
		node->argv = NULL;
		node->redirs = NULL;
	}
	ft_free_tab(pipes);
	return (node);
}*/

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

	rl_catch_signals = 0;
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
		if (!root)
		{
			free(line);
			continue ;
		}
		if (root->argv && root->argv[0] && ft_strcmp(root->argv[0],
				"exit") == 0)
		{
			free(line);
			builtin_exit(root->argv, &shell);
			free_node(root);
			return (0);
		}
		expand_tree(root, &shell);
		process_heredocs(root);
		execute_node(root, &shell);
		(free_node(root), free(line));
	}
	(ft_free_tab(shell.envp_array), free_env_list(shell.env));
	return (rl_clear_history(), shell.last_status);
}
