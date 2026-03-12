/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:23:12 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/07 16:43:48 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	add_or_update_env(t_shell *shell, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new = create_env_node(key, value);
	if (!new)
		return ;
	new->next = shell->env;
	shell->env = new;
}

int	builtin_export(char **argv, t_shell *shell)
{
	int		i;
	char	*eq;
	char	*key;
	char	*value;

	i = 1;
	while (argv[i])
	{
		eq = ft_strchr(argv[i], '=');
		if (!eq)
		{
			i++;
			continue ;
		}
		key = ft_substr(argv[i], 0, eq - argv[i]);
		value = ft_strdup(eq + 1);
		add_or_update_env(shell, key, value);
		free(key);
		free(value);
		i++;
	}
	return (0);
}
