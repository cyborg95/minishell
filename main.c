/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: w <w@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:27:07 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/02 07:15:27 by wngambi          ###   ########.fr       */
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

/*	=====================================================	*/

int	main(void)
{
	char		*line;
	t_malloc	*malloc_lst;
	t_cmd		*cmd_lst;

	malloc_lst = NULL;
	line = NULL;
	while (1)
	{
		if (read_prompt (&line, &malloc_lst) == false)
			continue ;
		cmd_lst = parse_input (line, &malloc_lst);
		if (!cmd_lst)
			continue ;
		display_cmd (cmd_lst);
		clean_lst_malloc (malloc_lst);
		malloc_lst = NULL;
	}
	return (0);
}

/*	=====================================================	*/

		//display_token (token_list);
