/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:47:29 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/23 17:26:14 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_case(t_redir **new, t_redir *src)
{
	if (!new || !src)
		return ;
	if (is_quoted(src->file))
		(*new)->expand = 0;
	else
		(*new)->expand = 1;
	(*new)->file = remove_quotes(src->file);
}

static void	new_head_not_empty(t_redir **new, t_redir **new_head)
{
	t_redir	*tmp;

	tmp = (*new_head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (*new);
}

t_redir	*convert_redirs(t_redir *src)
{
	t_redir	*new;
	t_redir	*new_head;

	new_head = NULL;
	while (src)
	{
		new = malloc (sizeof(t_redir));
		if (!new)
			return (NULL);
		new->type = convert_redir_type(src->type);
		if (new->type == R_HEREDOC)
			heredoc_case (&new, src);
		else
			new->file = ft_1strdup(src->file);
		new->fd = -1;
		new->next = NULL;
		if (!new_head)
			new_head = new;
		else
			new_head_not_empty (&new, &new_head);
		src = src->next;
	}
	return (new_head);
}

/*	==============================================	*/

static int	count_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	return (i);
}

t_node	*cmd_to_node(t_cmd *cmd)
{
	t_node	*node;
	int		i;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	ft_bzero (node, sizeof(t_node));
	node->type = NODE_CMD;
	i = count_args(cmd);
	node->argv = malloc(sizeof(char *) * (i + 1));
	if (!node->argv)
		return (NULL);
	ft_bzero(node->argv, sizeof(char *) * (i + 1));
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		node->argv[i] = ft_1strdup(cmd->args[i]);
		i++;
	}
	node->argv[i] = NULL;
	node->redirs = convert_redirs(cmd->redir);
	node->pid = 0;
	node->status = 0;
	return (node);
}
