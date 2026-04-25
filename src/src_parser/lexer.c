/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:01:58 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/25 11:06:22 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_word_state(t_word_state *state, char **line, char *word)
{
	state->line = line;
	state->word = word;
	state->i = 0;
	state->in_squote = false;
	state->in_dquote = false;
}

static bool	single_quote_case(t_word_state *state)
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

static bool	double_quote_case(t_word_state *state)
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

static bool	no_quote_case(t_word_state *state)
{
	if (!state->in_squote && !state->in_dquote)
	{
		if (is_space(**state->line) || is_operator(**state->line))
			return (true);
	}
	return (false);
}

static bool	backslash_case(t_word_state *state)
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
