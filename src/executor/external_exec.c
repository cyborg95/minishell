/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:01:19 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/24 17:51:09 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
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

static char	*try_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*path;

	tmp = ft_1strjoin(dir, "/");
	path = ft_1strjoin(tmp, cmd);
	free(tmp);
	if (access(path, X_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char	*path_finder(char *cmd, t_env *env)
{
	t_vars	vars;
	char	*res;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_1strdup(cmd));
	vars.path_env = my_getenv("PATH", env);
	if (!vars.path_env)
		return (NULL);
	vars.paths = ft_split(vars.path_env, ':');
	if (!vars.paths)
		return (NULL);
	vars.i = 0;
	while (vars.paths[vars.i])
	{
		res = try_path(vars.paths[vars.i], cmd);
		if (res)
			return (ft_free_tab(vars.paths), res);
		vars.i++;
	}
	ft_free_tab(vars.paths);
	return (NULL);
}
