/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 15:38:21 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/03 13:31:49 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
bool	is_back_slash(char c)
{
	if (c == '\\')
		return (true);
	else
		return (false);
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
bool	ends_with_backslash(char *line)
{
	int	i;

	if (!line)
		return (false);
	i = 0;
	while (line[i])
		i++;
	if (i == 0)
		return (false);
	i--;
	return (is_back_slash(line[i]));
}
/*
int	main(int ac, char **av)
{
	char	*line;

	(void)ac;
	line = av[1];
	if (ends_with_backslash (line))
		printf ("La str finit par un backslash");
	else
		printf ("Roule ma poule !\n");
}
*/

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
bool	is_pipe(char c)
{
	if (c == '|')
		return (true);
	else
		return (false);
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
bool	is_redir_in(char c)
{
	if (c == '<')
		return (true);
	return (false);
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
bool	is_redir_out(char c)
{
	if (c == '>')
		return (true);
	return (false);
}

/*	=====================================================	*/