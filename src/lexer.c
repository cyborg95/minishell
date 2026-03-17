/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:01:58 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/17 12:40:00 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	=====================================================	*/

static void	maj_quote(char c, bool *in_quote, char *quote)
{
	*quote = c;
	*in_quote = true;
}

static char	*extract_word(char **line, char *word)
{
	int		i;
	char	quote;
	bool	in_quote;

	if (!line)
		return (NULL);
	i = 0;
	in_quote = false;
	while (*line[0])
	{
		if (is_quote(*line[0]) && in_quote == false)
		{
			maj_quote (*line[0], &in_quote, &quote);
			(*line)++;
		}
		if ((is_quote(*line[0]) && *line[0] == quote) || is_space (*line[0])
			|| is_operator (*line[0]))
			break ;
		word[i++] = (*line[0]);
		(*line)++;
	}
	word[i] = '\0';
	return (word);
}

/*	=====================================================	*/

void	lexer(t_token **lst_token, t_malloc **lst_malloc, char *line)
{
	char	*word;
	int		i;

	if (!lst_token || !lst_malloc || !line)
		return ;
	word = malloc_remix (ft_strlen(line), lst_malloc);
	i = 0;
	while (*line)
	{
		while (is_space (*line))
			line++;
		if (!line)
			break ;
		if (is_operator (*line))
		{
			token_operator (line, lst_token, lst_malloc);
			line++;
		}
		else
		{
			word = extract_word (&line, word);
			create_token (word, WORD, lst_malloc, lst_token);
		}
	}
}
/*	=====================================================	*/

void	token_pipe(t_token **token_lst, t_malloc **lst_malloc)
{
	t_token	*token_pipe;

	if (!token_lst || !(*token_lst) || !lst_malloc || !(*lst_malloc))
		return ;
	token_pipe = create_token (NULL, PIPE, lst_malloc, token_lst);
}

/*	=====================================================	*/

void	token_redir_in(t_token **token_lst, t_malloc **lst_malloc)
{
	t_token	*token_redir_in;

	if (!token_lst)
		return ;
	token_redir_in = create_token (NULL, REDIR_IN, lst_malloc, token_lst);
}

/*	=====================================================	*/