/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:52:31 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/21 18:24:38 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	apply_redirections(t_redir *redirs, t_shell *shell)
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
			printf("minishell: %s: No such file or directory\n", redirs->file);
			shell->last_status = 1;
			return (-1);
		}
		if (redirs->type == R_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redirs = redirs->next;
	}
	return (0);
}
