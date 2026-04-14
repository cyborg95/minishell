/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:47:29 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/14 12:57:42 by otidahoh         ###   ########.fr       */
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

t_redir	*convert_redirs(t_redir *src, t_malloc **malloc_lst)
{
	t_redir	*new_head;
	t_redir	*new;
	t_redir	*tmp;

	new_head = NULL;
	while (src)
	{
		new = malloc_remix(sizeof(t_redir), malloc_lst);
		new->type = convert_redir_type(src->type);
		if (new->type == R_HEREDOC)
		{
			if (is_quoted(src->file))
				new->expand = 0;
			else
				new->expand = 1;
			new->file = remove_quotes(src->file, malloc_lst);
		}
		else
		{
			new->file = ft_strdup(src->file, malloc_lst);
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

t_node	*cmd_to_node(t_cmd *cmd, t_malloc **malloc_lst)
{
	t_node	*node;

	node = malloc_remix(sizeof(t_node), malloc_lst);
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	node->argv = cmd->args;
	node->redirs = convert_redirs(cmd->redir, malloc_lst);
	node->left = NULL;
	node->right = NULL;
	node->path = NULL;
	node->pid = 0;
	node->status = 0;
	return (node);
}

t_node	*cmd_list_to_ast(t_cmd *cmd, t_malloc **malloc_lst)
{
	t_node	*node;

	if (!cmd)
		return (NULL);
	if (!cmd->next)
		return (cmd_to_node(cmd, malloc_lst));
	node = malloc_remix(sizeof(t_node), malloc_lst);
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->left = cmd_to_node(cmd, malloc_lst);
	node->right = cmd_list_to_ast(cmd->next, malloc_lst);
	node->argv = NULL;
	node->redirs = NULL;
	return (node);
}
