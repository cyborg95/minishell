/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:00:14 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/22 20:13:36 by otidahoh         ###   ########.fr       */
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

static int	env_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}
static char	*env_to_str(t_env *env)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = strjoin(env->key, "=");
	if (!tmp1)
		return (NULL);
	tmp2 = strjoin(tmp1, env->value);
	free(tmp1);
	return (tmp2);
}

char	**env_list_to_array(t_env *env)
{
	char	**arr;
	int		i;
	int		count;

	count = env_size(env);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i] = env_to_str(env);
		if (!arr[i])
			return (NULL);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	*ft_itoa_remix(int n)
{
	long	nb;
	int		len;
	char	*str;

	nb = n;
	len = (n <= 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	str = malloc (sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}
