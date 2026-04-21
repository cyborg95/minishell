/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:01:19 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/21 11:02:33 by wngambi          ###   ########.fr       */
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

char	*my_getenv(char *name, t_env *env)
{
	int	j;

	j = ft_1strlen(name);
	while (env)
	{
		if (ft_strncmp(env->key, name, j) == 0 && env->key[j] == '\0')
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*path_finder(char *cmd, t_env *env)
{
	t_vars	vars;

	if (ft_strchr(cmd, '/'))
		return (ft_1strdup(cmd));
	vars.path_env = my_getenv("PATH", env);
	if (!vars.path_env)
		return (NULL);
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

int	execute_external(t_node *node, t_shell *shell, t_malloc **malloc_lst)
{
	int	sig;

	if (!node || !node->argv || !node->argv[0])
		return (1);
	if (!shell->envp_array)
		shell->envp_array = env_list_to_array(shell->env);
	node->path = path_finder(node->argv[0], shell->env);
	if (!node->path)
	{
		if (ft_strchr(node->argv[0], '/'))
		{
			printf("minishell: %s: No such file or directory\n", node->argv[0]);
			return (shell->last_status = 127, 127);
		}
		else
		{
			printf("minishell: %s: command not found\n", node->argv[0]);
			return (shell->last_status = 127, 127);
		}
	}
	node->pid = fork();
	if (node->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		apply_redirections(node->redirs, shell);
		execve(node->path, node->argv, shell->envp_array);
		if (errno == ENOENT)
		{
			perror(node->argv[0]);
			if (malloc_lst)
				clean_lst_malloc(malloc_lst);
			clean_node (node);
			clean_shell (shell);
			exit(127);
		}
		else if (errno == EACCES)
		{
			perror(node->argv[0]);
			if (malloc_lst)
				clean_lst_malloc(malloc_lst);
			clean_node (node);
			clean_shell (shell);
			exit(126);
		}
		else
		{
			perror(node->argv[0]);
			if (malloc_lst)
				clean_lst_malloc(malloc_lst);
			clean_node (node);
			clean_shell (shell);
			exit(1);
		}
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
	return (shell->last_status);
}
