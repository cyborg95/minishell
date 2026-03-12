/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:54:46 by otidahoh          #+#    #+#             */
/*   Updated: 2025/11/13 14:37:06 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_word(const char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	ft_memcpy(word, s, i);
	word[i] = '\0';
	return (word);
}

static void	ft_free_split(char **arr, int j)
{
	while (j-- > 0)
	{
		free(arr[j]);
	}
	free(arr);
}

static int	mini_split(char **word, char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word[j] = get_word(&s[i], c);
			if (!word[j])
				return (ft_free_split(word, j), 0);
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	word[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**output;

	if (!s)
		return (NULL);
	output = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!output)
		return (NULL);
	if (!mini_split(output, s, c))
		return (NULL);
	return (output);
}
