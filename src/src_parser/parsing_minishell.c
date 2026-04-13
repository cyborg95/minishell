/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 07:10:12 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/13 11:05:01 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

bool	read_prompt(char **line, t_malloc **malloc_lst)
{
	*line = remix_readline (PROMPT, malloc_lst);
	if (!line || !malloc_lst)
		return (false);
	if (is_only_space (*line))
		return (false);
	else if (ft_1strcmp(*line, EXIT) == 0)
	{
		clean_lst_malloc (*malloc_lst);
		(*malloc_lst) = NULL;
		printf("exit\n");
		exit (0);
	}
	while (!are_quotes_closed(*line) || ends_with_backslash (*line)
		|| (end_with_pipe(*line) && !is_operator_before (*line)))
		handle_multiligne_case (line, malloc_lst);
	return (true);
}

/*	=====================================================	*/

t_cmd	*parse_input(char *line, t_malloc **lst_malloc)
{
	t_token		*token_list;
	t_cmd		*cmd_lst;

	token_list = NULL;
	cmd_lst = NULL;
	init_token_lst (&token_list, lst_malloc, &line);
	if (!check_token_lst (&token_list, PROMPT, &line, lst_malloc))
		return (NULL);
	init_command_lst (token_list, lst_malloc, &cmd_lst);
	return (cmd_lst);
}

/*	=====================================================	*/