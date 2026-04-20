/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:33:35 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/20 11:52:05 by wngambi          ###   ########.fr       */
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
		if (ft_1strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	expand_argv(t_node *node, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!node || !node->argv)
		return ;
	while (node->argv[i])
	{
		tmp = expand_var(node->argv[i], shell);
		free (node->argv[i]);
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
