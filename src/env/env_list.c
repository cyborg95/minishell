/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:00:14 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/22 12:18:23 by wngambi          ###   ########.fr       */
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
	char	*tmp1;
	char	*tmp2;
	char	**arr;
	int		count;
	int		i;

	count = 0;
	i = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		tmp1 = strjoin(tmp->key, "=");
		if (!tmp1)
			return (NULL);
		tmp2 = strjoin(tmp1, tmp->value);
		free(tmp1);
		if (!tmp2)
			return (NULL);
		arr[i] = tmp2;
		tmp = tmp->next;
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
