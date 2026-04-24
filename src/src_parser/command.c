/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:31:08 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/24 12:10:38 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	=========================================================	*/

t_cmd	*create_cmd(t_malloc **lst_malloc, t_token *lst_token)
{
	t_cmd	*new_cmd;
	int		max_word;
	bool	after_redir;

	if (!lst_malloc || !lst_token)
		return (NULL);
	new_cmd = malloc_remix (sizeof(t_cmd), lst_malloc);
	ft_bzero (new_cmd, sizeof(t_cmd));
	max_word = 0;
	after_redir = false;
	while (lst_token)
	{
		if (is_redir (lst_token))
			after_redir = true;
		else if (after_redir && lst_token->type == WORD)
			after_redir = false;
		else if (lst_token->type == WORD && !after_redir)
			max_word++;
		lst_token = lst_token->next;
	}
	new_cmd->args = malloc_remix (sizeof(char *) * (max_word + 1), lst_malloc);
	ft_bzero(new_cmd->args, sizeof(char *) * (max_word + 1));
	return (new_cmd);
}

/*	=========================================================	*/

static void	add_back_args(t_cmd *cmd, char *word, t_malloc **lst_malloc)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd->args[i] != NULL)
		i++;
	cmd->args[i] = ft_strdup (word, lst_malloc);
	return ;
}

void	fill_cmd(t_token **lst_token, t_cmd *cmd, t_malloc **lst_malloc)
{
	if (!lst_token || !*lst_token)
		return ;
	while (*lst_token)
	{
		if ((*lst_token)->type == PIPE)
		{
			*lst_token = (*lst_token)->next;
			break ;
		}
		else if ((*lst_token)->type == WORD)
		{
			add_back_args(cmd, (*lst_token)->word, lst_malloc);
		}
		else if (is_redir((*lst_token)))
		{
			handle_redir(lst_malloc, lst_token, cmd);
			continue ;
		}
		*lst_token = (*lst_token)->next;
	}
}

/*	=========================================================	*/

void	add_back_cmd(t_cmd **lst_cmd, t_cmd *cmd, t_malloc **lst_malloc)
{
	t_cmd	*tmp;

	if (!lst_cmd || !cmd || !lst_malloc)
		return ;
	if ((*lst_cmd) == NULL)
		(*lst_cmd) = cmd;
	else
	{
		tmp = (*lst_cmd);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = cmd;
	}
}
