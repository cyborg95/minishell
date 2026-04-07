/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incomplete_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:56:23 by w                 #+#    #+#             */
/*   Updated: 2026/04/02 14:11:33 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	=====================================================	*/

bool	last_char_is_pipe(char *line)
{
	if (!line)
		return (false);
	while (*line)
		line++;
	line--;
	if (*line == '|')
		return (true);
	else
		return (false);
}

/*	=====================================================	*/

bool	is_incomplete_input(char *line)
{
	if (!are_quotes_closed(line))
		return (true);
	if (ends_with_backslash (line))
		return (true);
	if (last_char_is_pipe (line) && (ft_strlen(line) > 1))
		return (true);
	return (false);
}

/*	=====================================================	*/