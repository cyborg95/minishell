/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:01:58 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/21 15:42:16 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*extract_word(char **line, char *word)
{
	int		i;
	bool	s_quote;
	bool	d_quote;

	s_quote = false;
	d_quote = false;
	if (!line)
		return (NULL);
	i = 0;
	while (**line)
	{
		if (is_quote(**line))
			maj_quote (**line, &s_quote, &d_quote);
		else if (is_space (**line) && !s_quote && !d_quote)
			break ;
		else if ((is_operator (**line) && !s_quote && !d_quote))
			break ;
		word[i++] = (**line);
		(*line)++;
	}
	return (word[i] = '\0', word);
}

/*	=====================================================	*/

void	lexer(t_token **lst_token, t_malloc **lst_malloc, char *line)
{
	char	*word;
	int		i;

	if (!lst_token || !lst_malloc || !line)
		return ;
	word = malloc_remix ((ft_strlen(line) + 1) * sizeof(char), lst_malloc);
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
			create_token (ft_strdup (word, lst_malloc),
				WORD, lst_malloc, lst_token);
		}
	}
}
/*	=====================================================	*/

void	token_pipe(t_token **token_lst, t_malloc **lst_malloc)
{
	t_token	*token_pipe;

	if (!token_lst || !lst_malloc)
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