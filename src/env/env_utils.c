/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:33:35 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/03 12:27:20 by otidahoh         ###   ########.fr       */
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

void	expand_argv(t_node *node, t_shell *shell, t_malloc **malloc_lst)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!node || !node->argv)
		return ;
	while (node->argv[i])
	{
		tmp = expand_var(node->argv[i], shell, malloc_lst);
		free_remix(node->argv[i], malloc_lst);
		node->argv[i] = tmp;
		i++;
	}
}

void	expand_tree(t_node *node, t_shell *shell, t_malloc **malloc_lst)
{
	if (!node)
		return ;
	expand_argv(node, shell, malloc_lst);
	expand_tree(node->left, shell, malloc_lst);
	expand_tree(node->right, shell, malloc_lst);
}
