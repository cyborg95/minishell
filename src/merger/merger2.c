/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:22:13 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/23 17:24:46 by otidahoh         ###   ########.fr       */
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
	node->pid = 0;
	node->status = 0;
	node->path = NULL;
	node->left = cmd_to_node(cmd);
	node->right = cmd_list_to_ast(cmd->next);
	node->argv = NULL;
	node->redirs = NULL;
	return (node);
}
