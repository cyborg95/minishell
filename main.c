/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: w <w@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:27:07 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/25 18:38:15 by w                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Gerer le double free == CARRE
// Paufiner la detection des quotes non fermees == CARRE
// Coriger les quotes dans extrract word == CARRE
// Gerer le cas des doubles oeprateurs == CARRE
// Gerer le cas du backslash == CARRE
// Gerer le cas du backslah en derneir caractere qui refait un promt == CARRE


// gerer corectement les cas des multi lignes == CARRE
// COrrection du pipe seul == CARRE

/*	=====================================================	*/

int	main(void)
{
	char		*line;
	t_token		*token_list;
	t_malloc	*malloc_lst;

	malloc_lst = NULL;
	while (1)
	{
		token_list = NULL;
		line = remix_readline (PROMPT, &malloc_lst);
		if (!line || ft_strcmp(line, EXIT))
			break ;
		while (is_incomplete_input (line))
			handle_multiligne_case (&line, &malloc_lst);
		lexer (&token_list, &malloc_lst, &line);
		check_syntax (&token_list, PROMPT, &line, &malloc_lst);
	}
	clean_lst_malloc (malloc_lst);
	return (0);
}

/*	=====================================================	*/

		//display_token (token_list);

