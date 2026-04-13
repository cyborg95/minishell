/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 07:02:29 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/13 11:05:16 by wngambi          ###   ########.fr       */
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
