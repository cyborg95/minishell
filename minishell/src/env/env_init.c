/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:59:02 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/04 15:01:47 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*head;
	char	*eq;
	t_env	*new_node;
	int		i;

	i = 0;
	head = NULL;
	while (envp && envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		if (!eq)
			i++;
		else
		{
			new_node = malloc(sizeof(t_env));
			if (!new_node)
				exit(1);
			new_node->key = strndup(envp[i], eq - envp[i]);
			new_node->value = strdup(eq + 1);
			new_node->next = head;
			head = new_node;
			i++;
		}
	}
	return (head);
}
