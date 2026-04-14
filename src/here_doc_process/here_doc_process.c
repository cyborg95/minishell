/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 08:37:46 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/14 11:35:18 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_heredocs(t_node *node, t_malloc **lst_malloc)
{
	t_redir	*r;

	if (!node)
		return ;
	r = node->redirs;
	while (r)
	{
		if (r->type == R_HEREDOC)
			r->fd = handle_heredoc(r, lst_malloc);
		r = r->next;
	}
	process_heredocs(node->left, lst_malloc);
	process_heredocs(node->right, lst_malloc);
}

int	handle_heredoc(t_redir *redir, t_malloc **lst_malloc)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		return (perror("pipe"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!line || ft_1strcmp(line, redir->file) == 0)
		{
			add_malloc_in_lst(lst_malloc, create_node_malloc(line));
			break ;
		}
		write(fd[1], line, ft_1strlen(line));
		write(fd[1], "\n", 1);
		add_malloc_in_lst(lst_malloc, create_node_malloc(line));
	}
	close(fd[1]);
	return (fd[0]);
}
