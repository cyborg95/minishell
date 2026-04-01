/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: w <w@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:27:07 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/01 13:54:15 by wngambi          ###   ########.fr       */
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

void	init_command_lst(t_token *token_lst,
	t_malloc **malloc_lst, t_cmd **cmd_lst)
{
	t_cmd		*cmd;

	while (token_lst)
	{
		cmd = create_cmd (malloc_lst, token_lst);
		if (!cmd)
			break ;
		fill_cmd (&token_lst, cmd, malloc_lst);
		add_back_cmd (cmd_lst, cmd, malloc_lst);
	}
}

/*	=====================================================	*/

void	init_token_lst(t_token **token_lst, t_malloc **malloc_lst, char **line)
{
	lexer (token_lst, malloc_lst, line);
}

/*	=====================================================	*/

bool	read_prompt(char *line, t_malloc **malloc_lst)
{
	line = remix_readline (PROMPT, malloc_lst);
	if (!line || ft_strcmp(line, EXIT))
		return (false);
	while (!are_quotes_closed(line) || ends_with_backslash (line))
		handle_multiligne_case (&line, malloc_lst);
	return (true);
}

/*	=====================================================	*/

int	main(void)
{
	char		*line;
	t_token		*token_list;
	t_malloc	*malloc_lst;
	t_cmd		*cmd_lst;

	malloc_lst = NULL;
	while (1)
	{
		token_list = NULL;
		cmd_lst = NULL;
		if (read_prompt (line, &malloc_lst))
			continue ;
		init_token_lst (&token_list, &malloc_lst, &line);
		if (!check_token_lst (&token_list, PROMPT, &line, &malloc_lst))
			continue ;
		init_command_lst (token_list, &malloc_lst, &cmd_lst);
		display_cmd (cmd_lst);
	}
	clean_lst_malloc (malloc_lst);
	return (0);
}

/*	=====================================================	*/

		//display_token (token_list);
