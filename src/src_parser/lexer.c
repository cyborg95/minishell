/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:01:58 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/13 08:03:13 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (is_quote(*line))
		{
			if (is_single_quote(*line) && dquote == false)
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

/*	Carre on revient pas dessus	*/
static void	maj_quote(char c, bool *in_squote, bool *in_dquote)
{
	if (is_single_quote(c) && *in_dquote == false)
	{
		if (*in_squote == false)
			*in_squote = true;
		else
			*in_squote = false;
	}
	else if (is_double_quote(c) && *in_squote == false)
	{
		if (*in_dquote == false)
			*in_dquote = true;
		else
			*in_dquote = false;
	}
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
void	handle_multiligne_case(char **line, t_malloc **lst_malloc)
{
	char	*next_line;
	char	*tmp;
	char	*tmp2;

	if (!line)
		return ;
	next_line = remix_readline("> ", lst_malloc);
	if (!next_line)
		return ;
	if (ends_with_backslash(*line))
	{
		(*line)[strlen(*line) - 1] = '\0';
		tmp2 = ft_strjoin(*line, "", lst_malloc);
	}
	else
		tmp2 = ft_strjoin(*line, "\n", lst_malloc);
	tmp = ft_strjoin(tmp2, next_line, lst_malloc);
	(*line) = tmp;
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
void	back_slash_case(char **line, char *word)
{
	if (!line || !*line)
		return ;
	(*line)++;
	if (**line)
		*word = **line;
	(*line)++;
}

/*	=====================================================	*/

char	*extract_word(char **line, char *word)
{
	int		i;
	bool	in_squote;
	bool	in_dquote;

	if (!line)
		return (NULL);
	init_value (&in_squote, &in_dquote, &i);
	while (**line)
	{
		if (is_quote(**line) && ((**line == '\'' && !in_dquote)
				|| (**line == '"' && !in_squote)))
		{
			maj_quote(**line, &in_squote, &in_dquote);
			(*line)++;
			continue ;
		}
		else if (is_space (**line) && !in_squote && !in_dquote)
			break ;
		else if ((!in_squote && !in_dquote) && (is_operator (**line)
				|| is_space (**line) || (**line == '\0')))
			break ;
		word[i++] = (**line);
		(*line)++;
	}
	return (word[i] = '\0', word);
}
