/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:01:19 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/02 13:54:05 by otidahoh         ###   ########.fr       */
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

	j = ft_1strlen(name);
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
		return (ft_1strdup(cmd));
	vars.paths = ft_split(vars.path_env, ':');
	vars.i = 0;
	while (vars.paths && vars.paths[vars.i])
	{
		vars.tmp_path = ft_1strjoin(vars.paths[vars.i], "/");
		vars.path = ft_1strjoin(vars.tmp_path, cmd);
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
	return (NULL);
}

int	execute_external(t_node *node, t_shell *shell)
{
	int	sig;

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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		apply_redirections(node->redirs, shell);
		execve(node->path, node->argv, shell->envp_array);
		perror(node->argv[0]);
		exit(127);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(node->pid, &node->status, 0);
		if (WIFSIGNALED(node->status))
		{
			sig = WTERMSIG(node->status);
			if (sig == SIGINT)
				write(1, "\n", 1);
			else if (sig == SIGQUIT)
				write(1, "Quit (core dumped)\n", 20);
			shell->last_status = 128 + sig;
		}
		else
			shell->last_status = WEXITSTATUS(node->status);
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	return (free(node->path), shell->last_status);
}
