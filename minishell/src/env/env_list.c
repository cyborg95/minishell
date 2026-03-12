/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:00:14 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/07 17:55:00 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	**env_list_to_array(t_env *env)
{
	t_env	*tmp;
	char	**arr;

	env->count = 0;
	env->i = 0;
	tmp = env;
	while (tmp)
	{
		env->count++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(char *) * (env->count + 1));
	if (!arr)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		arr[env->i] = ft_strjoin(tmp->key, "=");
		arr[env->i] = ft_strjoin_free(arr[env->i], tmp->value);
		tmp = tmp->next;
		env->i++;
	}
	arr[env->i] = NULL;
	return (arr);
}
