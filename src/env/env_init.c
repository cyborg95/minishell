/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:59:02 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/25 15:28:03 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_back_env(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	char	*eq;
	int		i;

	head = NULL;
	i = 0;
	while (envp && envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			new_node = malloc(sizeof(t_env));
			if (!new_node)
				exit(1);
			new_node->key = strndup(envp[i], eq - envp[i]);
			new_node->value = ft_1strdup(eq + 1);
			new_node->next = NULL;
			add_back_env(&head, new_node);
		}
		i++;
	}
	return (head);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (strdup(s2));
	if (!s2)
		return (s1);
	len1 = strlen(s1);
	len2 = strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	strcpy(new_str, s1);
	strcpy(new_str + len1, s2);
	free(s1);
	return (new_str);
}
