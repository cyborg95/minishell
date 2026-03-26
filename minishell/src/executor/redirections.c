/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:52:31 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/19 18:25:28 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	apply_redirections(t_redir *redirs, t_shell *shell)
{
	int	fd;

	while (redirs)
	{
		if (redirs->type == R_IN)
			fd = open(redirs->file, O_RDONLY);
		else if (redirs->type == R_OUT)
			fd = open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redirs->type == R_APPEND)
			fd = open(redirs->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (redirs->type == R_HEREDOC)
		{
			dup2(redirs->fd, STDIN_FILENO);
			close(redirs->fd);
			redirs = redirs->next;
			continue ;
		}
		else
		{
			redirs = redirs->next;
			continue ;
		}
		if (fd < 0)
		{
			perror(redirs->file);
			shell->last_status = 1;
			return ;
		}
		if (redirs->type == R_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redirs = redirs->next;
	}
}
