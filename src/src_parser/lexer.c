/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:01:58 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/25 11:22:48 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_word(char **line, char *word)
{
	t_word_state	state;

	if (!line || !*line)
		return (NULL);
	init_word_state(&state, line, word);
	while (**line)
	{
		if (single_quote_case(&state))
			continue ;
		if (double_quote_case(&state))
			continue ;
		if (backslash_case(&state))
			continue ;
		if (no_quote_case(&state))
			break ;
		word[state.i++] = **line;
		(*line)++;
	}
	word[state.i] = '\0';
	return (word);
}
