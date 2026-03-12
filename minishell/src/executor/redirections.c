/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:52:31 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/09 12:45:38 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	apply_redirections2(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(redirs->file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redirections3(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(redirs->file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redirections4(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->file, O_RDONLY);
	if (fd < 0)
	{
		perror(redirs->file);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	apply_redirections(t_redir *redirs)
{
	int	fd;

	while (redirs)
	{
		if (redirs->type == R_IN)
		{
			fd = open(redirs->file, O_RDONLY);
			if (fd < 0)
			{
				perror(redirs->file);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redirs->type == R_OUT)
			apply_redirections2(redirs);
		else if (redirs->type == R_APPEND)
			apply_redirections3(redirs);
		else if (redirs->type == R_HEREDOC)
			apply_redirections4(redirs);
		redirs = redirs->next;
	}
}
