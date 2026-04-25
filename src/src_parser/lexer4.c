/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:42:30 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/25 10:25:58 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_escaped_double_quote(char *line, int i)
{
	int	backslash_count;

	backslash_count = 0;
	i--;
	while (i >= 0 && line[i] == '\\')
	{
		backslash_count++;
		i--;
	}
	return ((backslash_count % 2) == 1);
}

bool	are_quotes_closed(char *line)
{
	bool	squote;
	bool	dquote;
	int		i;

	squote = false;
	dquote = false;
	if (!line || !(*line))
		return (false);
	i = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			if (is_single_quote(line[i]) && dquote == false)
				squote = !squote;
			else if (is_double_quote(line[i]) && squote == false
				&& !is_escaped_double_quote(line, i))
				dquote = !dquote;
		}
		i++;
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