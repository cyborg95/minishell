/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 07:29:36 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/20 17:25:54 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	========================================================	*/

void	handle_redir(t_malloc **lst_malloc, t_token **lst_token, t_cmd *cmd)
{
	t_redir	*redir;

	if (!lst_malloc || !lst_token)
		return ;
	redir = create_redir (lst_malloc, (*lst_token)->type);
	(*lst_token) = (*lst_token)->next;
	redir->file = ft_1strdup((*lst_token)->word);
	add_back_redir (cmd, redir);
	*lst_token = (*lst_token)->next;
}

/*	========================================================	*/

t_redir	*create_redir(t_malloc **lst_malloc, int token_type)
{
	t_redir	*new_redir;

	new_redir = malloc_remix (sizeof(t_redir), lst_malloc);
	new_redir->type = token_type;
	new_redir->file = NULL;
	new_redir->next = NULL;
	return (new_redir);
}

/*	========================================================	*/

void	add_back_redir(t_cmd *cmd, t_redir *new_redir)
{
	if (!cmd || !new_redir)
		return ;
	if (cmd->redir == NULL)
		cmd->redir = new_redir;
	else
	{
		while (cmd->redir->next != NULL)
			cmd->redir = cmd->redir->next;
		cmd->redir->next = new_redir;
	}
}

/*	=====================================================	*/

void	display_redir(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->redir == NULL)
	{
		printf ("REDIR = NULL\n");
		return ;
	}
	while (cmd->redir)
	{
		if ((int)cmd->redir->type == (int)REDIR_IN)
			printf ("Type de redirection: [REDIR_IN],	");
		else if ((int)cmd->redir->type == (int)REDIR_OUT)
			printf ("Type de redirection: [REDIR_OUT],	");
		else if ((int)cmd->redir->type == (int)HEREDOC)
			printf ("Type de redirection: [HERE_DOC],	");
		else if ((int)cmd->redir->type == (int)APPEND)
			printf ("Type de redirection: [APPEND],		");
		printf ("file='%s'\n", cmd->redir->file);
		cmd->redir = cmd->redir->next;
	}
}

/*	=====================================================	*/