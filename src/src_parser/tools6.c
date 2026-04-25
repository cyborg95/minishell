/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 11:30:56 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/25 11:31:01 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"   

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
char	*remix_readline(const char	*prompt, t_malloc **lst_malloc)
{
	char		*line;
	t_malloc	*malloc_node;

	if (!prompt)
		return (NULL);
	line = readline (prompt);
	if (!line)
		return (NULL);
	if (!lst_malloc)
		return (line);
	malloc_node = create_node_malloc (line);
	if (!malloc_node)
		return (line);
	add_malloc_in_lst (lst_malloc, malloc_node);
	return (line);
}

/*	=====================================================	*/