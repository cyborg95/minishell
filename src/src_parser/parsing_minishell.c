/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 07:10:12 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/25 11:09:46 by wngambi          ###   ########.fr       */
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

static bool	is_dquote(char c)
{
	if (c == 34)
		return (true);
	else
		return (false);
}

static bool	word_in_dquote(char *word)
{
	int	size;

	if (!word)
		return (false);
	size = ft_strlen (word);
	if (size <= 2)
		return (false);
	if (is_dquote (word[0]) && is_dquote (word[size - 1]))
		return (true);
	else
		return (false);
}

static bool	backslash_before_last_dquote(char *word)
{
	int	index_last_word;

	if (!word)
		return (false);
	else
	{
		index_last_word = ft_strlen (word);
		index_last_word--;
		if (!is_dquote (word[index_last_word]))
			return (false);
		index_last_word--;
		if (word[index_last_word] == 92)
			return (true);
	}
	return (false);
}

static int	count_word_willy(char *word)
{
	int		i;
	int		total_word;
	bool	nw;

	if (!word)
		return (0);
	i = -1;
	total_word = 0;
	nw = true;
	while (word[++i])
	{
		if (!is_space (word[i]) && nw)
		{
			total_word++;
			nw = !nw;
		}
		else if (is_space (word[i]) && !nw)
			nw = !nw;
	}
	return (total_word);
}


char	*get_last_word(char *s, t_malloc **lst_malloc)
{
	int	i;
	int	end;
	int	start;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	while (--i >= 0 && is_space(s[i]))
		;
	if (i < 0)
		return (NULL);
	end = i;
	while (i >= 0 && !is_space(s[i]))
		i--;
	start = i + 1;
	return (ft_strndup(s + start, end - start + 1, lst_malloc));
}

static bool	last_word_in_dquote_and_backslash_before_last_dquote(char *word,
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

static void	free_token_lst(t_token **token_lst, t_malloc **lst_malloc)
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
	free_token_lst (&token_list, lst_malloc);
	return (cmd_lst);
}

/*	=====================================================	*/