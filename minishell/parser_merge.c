/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_merge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:15:00 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/27 14:36:57 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_token	*find_pipe(t_token *tok)
{
	while (tok)
	{
		if (tok->type == PIPE)
			return (tok);
		tok = tok->next;
	}
	return (NULL);
}

int	count_args_tokens(t_token *tok)
{
	int	count;

	count = 0;
	while (tok)
	{
		if (tok->type == WORD)
			count++;
		tok = tok->next;
	}
	return (count);
}

char	**extract_args(t_token *tok)
{
	int		count , i, j;
	t_token	*current;
	t_type	prev_type;
	char	**argv;

	count = 0, i = 0, j = 0;
	current = tok;
	prev_type = 0;
	while (current)
	{
		if (current->type == WORD && prev_type != REDIR_IN
			&& prev_type != REDIR_OUT && prev_type != APPEND
			&& prev_type != HEREDOC)
			count++;
		prev_type = current->type;
		current = current->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	current = tok;
	prev_type = 0;
	while (current)
	{
		if (current->type == WORD && prev_type != REDIR_IN
			&& prev_type != REDIR_OUT && prev_type != APPEND
			&& prev_type != HEREDOC)
			argv[j++] = strdup(current->word);
		prev_type = current->type;
		current = current->next;
	}
	argv[j] = NULL;
	return (argv);
}

t_redir	*extract_redirs(t_token *tok)
{
	t_redir	*head;
	t_redir	*new;

	head = NULL;
	while (tok)
	{
		if (tok->type == REDIR_IN || tok->type == REDIR_OUT
			|| tok->type == APPEND || tok->type == HEREDOC)
		{
			new = malloc(sizeof(t_redir));
			new->next = NULL;
			if (tok->type == REDIR_IN)
				new->type = R_IN;
			else if (tok->type == REDIR_OUT)
				new->type = R_OUT;
			else if (tok->type == APPEND)
				new->type = R_APPEND;
			else
				new->type = R_HEREDOC;
			tok = tok->next;
			new->file = strdup(tok->word);
			add_redir_back(&head, new);
		}
		tok = tok->next;
	}
	return (head);
}

t_node	*build_cmd(t_token *tok)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = NODE_CMD;
	node->argv = extract_args(tok);
	node->redirs = extract_redirs(tok);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	*tokens_to_ast(t_token *tok)
{
	t_token	*pipe_tok;
	t_node	*node;
	t_token	*right;

	pipe_tok = find_pipe(tok);
	if (!pipe_tok)
		return (build_cmd(tok));
	node = malloc(sizeof(t_node));
	node->type = NODE_PIPE;
	right = pipe_tok->next;
	pipe_tok->next = NULL;
	node->left = tokens_to_ast(tok);
	node->right = tokens_to_ast(right);
	return (node);
}
