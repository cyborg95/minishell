/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:01:19 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/11 16:38:55 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*my_getenv(char *name, char **env)
{
	int	i;
	int	j;

	j = ft_strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], name, j) == 0 && env[i][j] == '=')
			return (env[i] + j + 1);
		i++;
	}
	return (NULL);
}

char	*path_finder(char *cmd, char **envp)
{
	t_vars	vars;

	vars.path_env = my_getenv("PATH", envp);
	if (!vars.path_env)
		return (ft_strdup(cmd));
	vars.paths = ft_split(vars.path_env, ':');
	vars.i = 0;
	while (vars.paths && vars.paths[vars.i])
	{
		vars.tmp_path = ft_strjoin(vars.paths[vars.i], "/");
		vars.path = ft_strjoin(vars.tmp_path, cmd);
		free(vars.tmp_path);
		if (access(vars.path, X_OK) == 0)
		{
			ft_free_tab(vars.paths);
			return (vars.path);
		}
		free(vars.path);
		vars.i++;
	}
	ft_free_tab(vars.paths);
	return (ft_strdup(cmd));
}

int	execute_external(t_node *node, t_shell *shell)
{
	if (!node || !node->argv || !node->argv[0])
		return (1);
	if (!shell->envp_array)
		shell->envp_array = env_list_to_array(shell->env);
	node->path = path_finder(node->argv[0], shell->envp_array);
	if (!node->path)
	{
		printf("minishell: %s: command not found\n", node->argv[0]);
		return (shell->last_status = 127, 127);
	}
	node->pid = fork();
	if (node->pid == 0)
	{
		execve(node->path, node->argv, shell->envp_array);
		perror(node->argv[0]);
		exit(127);
	}
	else
	{
		(signal(SIGINT, handle_signal2), signal(SIGQUIT, handle_signal2));
		waitpid(node->pid, &node->status, 0);
		shell->last_status = WEXITSTATUS(node->status);
		(signal(SIGINT, handle_signal), signal(SIGQUIT, SIG_IGN));
	}
	return (free(node->path), shell->last_status);
}
