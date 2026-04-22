/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 07:02:29 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/22 11:04:44 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	================================================	*/

bool	end_with_pipe(char *line)
{
	int	i;

	if (!line)
		return (false);
	i = ft_strlen (line) - 1;
	while (i >= 0 && is_space(line[i]))
		i--;
	if (i >= 0 && line[i] == '|')
		return (true);
	else
		return (false);
}

/*	================================================	*/

bool	is_operator_before(char *line)
{
	int	i;

	if (!line)
		return (false);
	if (!end_with_pipe (line))
		return (false);
	i = ft_strlen (line) - 1;
	while (i >= 0 && is_space(line[i]))
		i--;
	i--;
	while (i >= 0 && is_space(line[i]))
		i--;
	if (is_operator (line[i]))
		return (true);
	else
		return (false);
}

/*	================================================	*/

bool	is_only_space(char *str)
{
	int	i;

	if (!str)
		return (false);
	else
	{
		i = 0;
		while (str[i])
		{
			if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
				i++;
			else
				return (false);
		}
	}
	return (true);
}

/*	================================================	*/

char	*strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;
	int		total_size;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (strdup(s2));
	if (!s2)
		return (strdup(s1));
	total_size = (ft_strlen (s1) + ft_strlen (s2));
	res = malloc(total_size + 1);
	if (!res)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < ft_strlen (s1))
		res[i] = s1[i];
	while (++j < ft_strlen(s2))
		res[i + j] = s2[j];
	res[i + j] = '\0';
	return (res);
}
