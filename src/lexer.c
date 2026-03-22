/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:01:58 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/22 16:00:41 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	are_quotes_closed(char *line)
{
	bool	squote;
	bool	dquote;

	squote = false;
	dquote = false;
	if (!line && !(*line))
		return (false);
	while (*line)
	{
		if (is_quote (*line))
		{
			if (is_single_quote (*line) && dquote == false)
				squote = !squote;
			else if (is_double_quote(*line) && squote == false)
				dquote = !dquote;
		}
		line++;
	}
	if (squote == false && dquote == false)
		return (true);
	return (false);
}

/*	=====================================================	*/

static void	maj_quote(char c, bool *s_quote, bool *d_quote)
{
	const char	single_quote = '\'';
	const char	double_quote = '"';

	if (c == single_quote && *s_quote == false)
		*s_quote = true;
	else if (c == single_quote && *s_quote == true)
		*s_quote = false;
	else if (c == double_quote && *d_quote == false)
		*d_quote = true;
	else if (c == double_quote && *d_quote == true)
		*d_quote = false;
}

/*	=====================================================	*/

void	handle_multiligne_case(char **line, t_malloc **lst_malloc)
{
	char	*next_line;
	char	*tmp;

	if (!line)
		return ;
	next_line = remix_readline ("> ", lst_malloc);
	if (!next_line)
		return ;
	tmp = ft_strjoin (*line, next_line, lst_malloc);
	(*line) = tmp;
}

/*	=====================================================	*/

void	back_slash_case(char **line, char *word)
{
	if (!line || !*line)
		return ;
	(*line)++;
	if (**line)
		*word = **line;
	(*line)++;
}

static char	*extract_word(char **line, char *word)
{
	int		i;
	bool	in_squote;
	bool	in_dquote;

	in_squote = false;
	in_dquote = false;
	if (!line)
		return (NULL);
	i = 0;
	while (**line)
	{
		if (is_quote(**line))
			maj_quote (**line, &in_squote, &in_dquote);
		else if (is_space (**line) && !in_squote && !in_dquote)
			break ;
		else if ((!in_squote && !in_dquote) && (is_operator (**line)
				|| is_space (**line) || (**line == '\0')))
			break ;
		else if (**line == '\\' && !in_squote)
			back_slash_case(line, &word[i++]);
		word[i++] = (**line);
		(*line)++;
	}
	return (word[i] = '\0', word);
}

/*	=====================================================	*/

void	lexer(t_token **lst_token, t_malloc **lst_malloc, char **line)
{
	char	*word;

	if (!lst_token || !lst_malloc || !line)
		return ;
	word = malloc_remix ((ft_strlen(*line) + 1) * sizeof(char), lst_malloc);
	while (**line)
	{
		while (is_space (**line))
			(*line)++;
		if (!*line)
			break ;
		if (is_operator (**line))
			token_operator (line, lst_token, lst_malloc);
		else
		{
			word = extract_word (line, word);
			create_token (ft_strdup (word, lst_malloc),
				WORD, lst_malloc, lst_token);
		}
	}
}
/*	=====================================================	*/

void	token_pipe(t_token **token_lst, t_malloc **lst_malloc)
{
	if (!token_lst || !lst_malloc)
		return ;
	create_token (NULL, PIPE, lst_malloc, token_lst);
}

/*	=====================================================	*/

void	token_redir_in(t_token **token_lst, t_malloc **lst_malloc)
{
	if (!token_lst)
		return ;
	create_token (NULL, REDIR_IN, lst_malloc, token_lst);
}

/*	=====================================================	*/