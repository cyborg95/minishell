/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 08:37:46 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/26 11:15:26 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*remove_quotes(char *s)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc (ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	while (s[i])
	{
		if (s[i] != '"' && s[i] != '\'')
			new[j++] = s[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

void	close_heredocs(t_node *node)
{
	t_redir	*r;

	if (!node)
		return ;
	r = node->redirs;
	while (r)
	{
		if (r->type == R_HEREDOC && r->fd >= 0)
		{
			close(r->fd);
			r->fd = -1;
		}
		r = r->next;
	}
	close_heredocs(node->left);
	close_heredocs(node->right);
}

void	process_heredocs(t_node *node, t_shell *shell, t_malloc **lst_malloc)
{
	t_redir	*r;

	if (!node)
		return ;
	r = node->redirs;
	while (r)
	{
		if (r->type == R_HEREDOC)
			r->fd = handle_heredoc(r, shell, lst_malloc);
		r = r->next;
	}
	process_heredocs(node->left, shell, lst_malloc);
	process_heredocs(node->right, shell, lst_malloc);
}

int	handle_heredoc(t_redir *redir, t_shell *shell, t_malloc **lst_malloc)
{
	int		fd[2];
	char	*line;
	char	*expanded;

	if (pipe(fd) < 0)
		return (perror("pipe"), -1);
	while (1)
	{
		line = remix_readline("> ", lst_malloc);
		if (!line)
			break ;
		if (ft_1strcmp(line, redir->file) == 0)
			break ;
		expanded = line;
		if (redir->expand)
			expanded = expand_var(line, shell);
		write(fd[1], expanded, ft_1strlen(expanded));
		if (redir->expand)
			free(expanded);
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	return (fd[0]);
}
