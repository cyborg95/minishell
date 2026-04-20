/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:47:29 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/20 11:31:22 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_type	convert_redir_type(int type)
{
	if (type == REDIR_IN)
		return (R_IN);
	if (type == REDIR_OUT)
		return (R_OUT);
	if (type == APPEND)
		return (R_APPEND);
	if (type == HEREDOC)
		return (R_HEREDOC);
	return (R_IN);
}

t_redir	*convert_redirs(t_redir *src)
{
	t_redir	*new_head;
	t_redir	*new;
	t_redir	*tmp;

	new_head = NULL;
	while (src)
	{
		new = malloc (sizeof(t_redir));
		new->type = convert_redir_type(src->type);
		if (new->type == R_HEREDOC)
		{
			if (is_quoted(src->file))
				new->expand = 0;
			else
				new->expand = 1;
			new->file = remove_quotes(src->file);
		}
		else
		{
			new->file = strdup(src->file);
		}
		new->fd = -1;
		new->next = NULL;
		if (!new_head)
			new_head = new;
		else
		{
			tmp = new_head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		src = src->next;
	}
	return (new_head);
}

t_node	*cmd_to_node(t_cmd *cmd)
{
	t_node	*node;
	int		i;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	i = 0;
	while (cmd->args && cmd->args[i])
		i++;

	node->argv = malloc(sizeof(char *) * (i + 1));
	if (!node->argv)
		return (NULL);

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		node->argv[i] = strdup(cmd->args[i]);
		i++;
	}
	node->argv[i] = NULL;
	node->redirs = convert_redirs(cmd->redir);
	node->left = NULL;
	node->right = NULL;
	node->path = NULL;
	node->pid = 0;
	node->status = 0;
	return (node);
}

t_node	*cmd_list_to_ast(t_cmd *cmd)
{
	t_node	*node;

	if (!cmd)
		return (NULL);
	if (!cmd->next)
		return (cmd_to_node(cmd));
	node = malloc (sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->left = cmd_to_node(cmd);
	node->right = cmd_list_to_ast(cmd->next);
	node->argv = NULL;
	node->redirs = NULL;
	return (node);
}
