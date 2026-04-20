/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_minishell2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 10:07:38 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/20 18:44:07 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	====================================================	*/


void	clean_history_malloc_shell(t_shell *shell, t_malloc **lst_malloc)
{
	clean_lst_malloc (lst_malloc);
	(*lst_malloc) = NULL;
	clean_shell(shell);
	rl_clear_history();
}

/*	====================================================	*/

void	clean_line(char *line)
{
	if (!line)
		return ;
	else
		free (line);
}
/*	====================================================	*/

static void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	clean_node(t_node *node)
{
	if (!node)
		return;

	// gauche / droite (AST récursif)
	clean_node(node->left);
	clean_node(node->right);

	// argv
	if (node->argv)
		ft_free_tab(node->argv);

	// redirections
	if (node->redirs)
		free_redir(node->redirs);

	// path (résultat exec)
	/*if (node->path)
		free(node->path);*/

	// node lui-même
	free(node);
}