/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:56:13 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/21 14:13:16 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	==========================================	*/

// Operationnel on revient pas dessus
bool	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

/*	==========================================	*/

// Operationnel on revient pas dessus
bool	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

/*	==========================================	*/

// Operationnel on revient pas dessus
bool	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (true);
	return (false);
}

/*	==========================================	*/

// Operationnel on revient pas dessus
int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*	==========================================	*/

// Operationnel on revient pas dessus
char	*ft_strdup(char *str, t_malloc **lst_malloc)
{
	char	*word;
	int		size;
	int		i;

	if (!str)
		return (NULL);
	size = ft_strlen (str);
	word = malloc_remix (sizeof(char) * (size + 1), lst_malloc);
	if (!word)
		return (NULL);
	i = 0;
	while (str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

/*	==========================================	*/