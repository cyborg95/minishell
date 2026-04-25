/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 07:10:12 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/25 11:29:51 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_dquote(char c)
{
	if (c == 34)
		return (true);
	else
		return (false);
}

bool	word_in_dquote(char *word)
{
	int	size;

	if (!word)
		return (false);
	size = ft_strlen (word);
	if (size <= 2)
		return (false);
	if (is_dquote (word[0]) && is_dquote (word[size - 1]))
		return (true);
	else
		return (false);
}

bool	backslash_before_last_dquote(char *word)
{
	int	index_last_word;

	if (!word)
		return (false);
	else
	{
		index_last_word = ft_strlen (word);
		index_last_word--;
		if (!is_dquote (word[index_last_word]))
			return (false);
		index_last_word--;
		if (word[index_last_word] == 92)
			return (true);
	}
	return (false);
}

int	count_word_willy(char *word)
{
	int		i;
	int		total_word;
	bool	nw;

	if (!word)
		return (0);
	i = -1;
	total_word = 0;
	nw = true;
	while (word[++i])
	{
		if (!is_space (word[i]) && nw)
		{
			total_word++;
			nw = !nw;
		}
		else if (is_space (word[i]) && !nw)
			nw = !nw;
	}
	return (total_word);
}

char	*get_last_word(char *s, t_malloc **lst_malloc)
{
	int	i;
	int	end;
	int	start;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	while (--i >= 0 && is_space(s[i]))
		;
	if (i < 0)
		return (NULL);
	end = i;
	while (i >= 0 && !is_space(s[i]))
		i--;
	start = i + 1;
	return (ft_strndup(s + start, end - start + 1, lst_malloc));
}
