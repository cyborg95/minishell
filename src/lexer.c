/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:01:58 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/02 06:23:52 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	=====================================================	*/

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

char	*extract_word(char **line, char *word)
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