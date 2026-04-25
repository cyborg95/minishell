/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 11:25:49 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/25 14:31:35 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

/*	===================================================== */

bool	last_word_in_dquote_and_backslash_before_last_dquote(char *word,
	t_malloc **lst_malloc)
{
	int		size;
	char	*last_word;

	if (!word)
		return (false);
	size = ft_strlen (word);
	if (size <= 2)
		return (false);
	if (count_word_willy (word) <= 1)
	{
		if (word_in_dquote (word) && backslash_before_last_dquote (word))
			return (true);
		return (false);
	}
	else
	{
		last_word = get_last_word (word, lst_malloc);
		if (!last_word)
			return (false);
		if (word_in_dquote (last_word)
			&& backslash_before_last_dquote (last_word))
			return (true);
		else
			return (false);
	}
}

bool	read_prompt(char **line, t_malloc **lst_malloc)
{
	if (!line || !lst_malloc)
		return (false);
	*line = remix_readline ("minishell> ", lst_malloc);
	if (*line == NULL)
		return (false);
	if (is_only_space (*line))
		return (true);
	while (!are_quotes_closed(*line) || ends_with_backslash (*line)
		|| last_word_in_dquote_and_backslash_before_last_dquote (*line,
			lst_malloc))
		handle_multiligne_case (line, lst_malloc);
	return (true);
}

/*	=====================================================	*/

void	free_token_lst(t_token **token_lst, t_malloc **lst_malloc)
{
	t_token	*tmp;
	bool	end_of_lst;

	if (!token_lst || !(*token_lst))
		return ;
	end_of_lst = false;
	while (*token_lst)
	{
		if ((*token_lst)->next)
			tmp = (*token_lst)->next;
		else
			end_of_lst = true;
		if ((*token_lst)->word)
			free_remix ((*token_lst)->word, lst_malloc);
		free_remix ((*token_lst), lst_malloc);
		if (end_of_lst)
			break ;
		else
			*token_lst = tmp;
	}
	*token_lst = NULL;
}
