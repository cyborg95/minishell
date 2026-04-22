/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:52:31 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/22 19:35:42 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	open_redir(t_redir *r)
{
	int	fd;

	fd = -1;
	if (r->type == R_IN)
		fd = open(r->file, O_RDONLY);
	else if (r->type == R_OUT)
		fd = open(r->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (r->type == R_APPEND)
		fd = open(r->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

static void	apply_fd(int fd, t_redir *r)
{
	if (r->type == R_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	hd_heredoc(t_redir *r)
{
	dup2(r->fd, STDIN_FILENO);
	close(r->fd);
}

int	apply_redirections(t_redir *redirs, t_shell *shell)
{
	int	fd;

	while (redirs)
	{
		if (redirs->type == R_HEREDOC)
			hd_heredoc(redirs);
		else
		{
			fd = open_redir(redirs);
			if (fd < 0)
			{
				printf("minishell: %s: No such file or directory\n",
					redirs->file);
				shell->last_status = 1;
				return (-1);
			}
			apply_fd(fd, redirs);
		}
		redirs = redirs->next;
	}
	return (0);
}
