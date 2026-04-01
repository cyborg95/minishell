/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:31:08 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/01 14:04:50 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*	=========================================================	*/

/*
void	display_cmd(t_cmd *cmd_lst)
{
	int	i;

	i = 0;
	if (!cmd_lst)
		return ;
	while (cmd_lst)
	{
		printf ("=======================================================\n");
		printf ("\n\nAFFICHAGE DE LA COMMANDE NUMERO: %d\n\n", i++);
		printf ("=======================================================\n");
		printf ("=======================================================\n\n");
		display_args (cmd_lst->args);
		display_redir (cmd_lst);
		cmd_lst = cmd_lst->next;
	}
}
*/

void	display_cmd(t_cmd *cmd_lst)
{
	int	cmd_index = 1;

	if (!cmd_lst)
	{
		printf("No command to display\n");
		return ;
	}

	while (cmd_lst)
	{
		printf("\n");
		printf("╔══════════════════════════════════════╗\n");
		printf("║          COMMAND [%d]                ║\n", cmd_index++);
		printf("╚══════════════════════════════════════╝\n");
		printf("  ➤ ARGS:\n");

		if (!cmd_lst->args || !cmd_lst->args[0])
			printf("     (none)\n");
		else
		{
			int i = 0;
			while (cmd_lst->args[i])
			{
				printf("     [%d] -> \"%s\"\n", i, cmd_lst->args[i]);
				i++;
			}
		}
		printf("  ➤ REDIRECTIONS:\n");

		if (!cmd_lst->redir)
			printf("     (none)\n");
		else
		{
			t_redir *r = cmd_lst->redir;

			while (r)
			{
				if (r->type == REDIR_IN)
					printf("     <    \"%s\"\n", r->file);
				else if (r->type == REDIR_OUT)
					printf("     >    \"%s\"\n", r->file);
				else if (r->type == APPEND)
					printf("     >>   \"%s\"\n", r->file);
				else if (r->type == HEREDOC)
					printf("     <<   \"%s\"\n", r->file);
				else
					printf("     ?    \"%s\" (unknown type)\n", r->file);

				r = r->next;
			}
		}

		cmd_lst = cmd_lst->next;
	}
	printf("\n");
}

/*	=========================================================	*/
