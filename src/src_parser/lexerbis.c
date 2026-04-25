/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerbis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 11:22:34 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/25 11:24:59 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_word_state(t_word_state *state, char **line, char *word)
{
	state->line = line;
	state->word = word;
	state->i = 0;
	state->in_squote = false;
	state->in_dquote = false;
}

bool	single_quote_case(t_word_state *state)
{
	if (**state->line == '\'' && !state->in_dquote)
	{
		state->in_squote = !state->in_squote;
		state->word[(state->i)++] = **state->line;
		(*state->line)++;
		return (true);
	}
	return (false);
}

bool	double_quote_case(t_word_state *state)
{
	if (**state->line == '"' && !state->in_squote)
	{
		state->in_dquote = !state->in_dquote;
		state->word[(state->i)++] = **state->line;
		(*state->line)++;
		return (true);
	}
	return (false);
}

bool	no_quote_case(t_word_state *state)
{
	if (!state->in_squote && !state->in_dquote)
	{
		if (is_space(**state->line) || is_operator(**state->line))
			return (true);
	}
	return (false);
}

bool	backslash_case(t_word_state *state)
{
	if (**state->line != '\\' || state->in_dquote)
		return (false);
	if (*(*state->line + 1) == '\0')
		return (false);
	(*state->line)++;
	state->word[(state->i)++] = **state->line;
	(*state->line)++;
	return (true);
}
