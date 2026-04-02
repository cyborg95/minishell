/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:56:13 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/26 14:44:11 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Operationnel on revient pas dessus
bool	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

/*	==========================================	*/

// Operationnel on revient pas dessus
bool	is_single_quote(char c)
{
	if (c == '\'')
		return (true);
	else
		return (false);
}

// Operationnel on revient pas dessus
bool	is_double_quote(char c)
{
	if (c == '"')
		return (true);
	else
		return (false);
}

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