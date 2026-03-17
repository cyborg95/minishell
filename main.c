/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:27:07 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/17 12:28:22 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	=====================================================	*/

int	main(void)
{
	char		*line;
	t_token		*token_list;
	t_malloc	*malloc_lst;

	token_list = NULL;
	malloc_lst = NULL;
	while (1)
	{
		line = readline ("minishell> ");
		if (!line)
			break ;
		lexer (&token_list, &malloc_lst, line);
	}
	display_token (token_list);
	clean_lst_malloc (malloc_lst);
	clean_token (&token_list);
	return (0);
}

/*	=====================================================	*/