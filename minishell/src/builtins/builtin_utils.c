/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:21:55 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/07 17:28:23 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stddef.h>
#include <stdio.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static int	execute_builtin2(t_node *node, t_shell *shell)
{
	if (ft_strcmp(node->argv[0], "export") == 0)
	{
		shell->last_status = builtin_export(node->argv, shell);
		return (1);
	}
	if (ft_strcmp(node->argv[0], "unset") == 0)
	{
		shell->last_status = builtin_unset(node->argv, shell);
		return (1);
	}
	if (ft_strcmp(node->argv[0], "exit") == 0)
	{
		builtin_exit(node->argv, shell);
		return (1);
	}
	return (0);
}

int	execute_builtin(t_node *node, t_shell *shell)
{
	if (!node || !node->argv || !node->argv[0])
		return (0);
	if (ft_strcmp(node->argv[0], "cd") == 0)
	{
		shell->last_status = builtin_cd(node->argv, shell);
		return (1);
	}
	if (ft_strcmp(node->argv[0], "echo") == 0)
	{
		shell->last_status = builtin_echo(node->argv);
		return (1);
	}
	if (ft_strcmp(node->argv[0], "pwd") == 0)
	{
		shell->last_status = builtin_pwd();
		return (1);
	}
	if (ft_strcmp(node->argv[0], "env") == 0)
	{
		shell->last_status = builtin_env(shell->env);
		return (1);
	}
	execute_builtin2(node, shell);
	return (0);
}
