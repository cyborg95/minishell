/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:27:07 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/21 19:58:37 by wngambi          ###   ########.fr       */
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
		while (!are_quotes_closed(line))
			handle_unclosed_quote (&line, &malloc_lst);
		lexer (&token_list, &malloc_lst, line);
		free (line);
	}
	display_token (token_list);
	clean_lst_malloc (malloc_lst);
	return (0);
}

/*	=====================================================	*/

