/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:42:30 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/22 12:49:26 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	are_quotes_closed(char *line)
{
	bool	squote;
	bool	dquote;

	squote = false;
	dquote = false;
	if (!line || !(*line))
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