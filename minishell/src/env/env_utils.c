/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:33:35 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/09 12:31:26 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*expand_var(char *arg, t_shell *shell)
{
	char	*value;

	if (arg[0] != '$')
		return (ft_strdup(arg));
	value = get_env_value(shell->env, arg + 1);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

void	expand_argv(t_node *node, t_shell *shell)
{
	int		i;
	char	*tmp;

	if (!node || !node->argv)
		return ;
	i = 0;
	while (node->argv[i])
	{
		tmp = expand_var(node->argv[i], shell);
		free(node->argv[i]);
		node->argv[i] = tmp;
		i++;
	}
}

void	expand_tree(t_node *node, t_shell *shell)
{
	if (!node)
		return ;
	expand_argv(node, shell);
	expand_tree(node->left, shell);
	expand_tree(node->right, shell);
}
