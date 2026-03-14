/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:23:12 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/14 15:09:37 by otidahoh         ###   ########.fr       */
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
	if (!new->key)
		return (free(new), NULL);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
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
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = NULL;
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

static void	process_export_arg(t_shell *shell, char *arg)
{
	char	*eq;
	char	*key;

	if (!is_valid_identifier(arg))
	{
		printf("export: `%s': not a valid identifier\n", arg);
		return ;
	}
	eq = ft_strchr(arg, '=');
	if (!eq)
		add_or_update_env(shell, arg, NULL);
	else
	{
		key = ft_substr(arg, 0, eq - arg);
		add_or_update_env(shell, key, eq + 1);
		free(key);
	}
}

int	builtin_export(char **argv, t_shell *shell)
{
	int	in;

	if (!argv[1])
		return (printable_export(shell));
	in = 1;
	while (argv[in])
	{
		process_export_arg(shell, argv[in]);
		in++;
	}
	return (0);
}
