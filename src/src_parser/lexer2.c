/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:09:34 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/17 06:44:32 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		{
			token_operator (line, lst_token, lst_malloc);
			(*line)++;
		}
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
	create_token (ft_strdup ("|", lst_malloc), PIPE, lst_malloc, token_lst);
}.0

/*	=====================================================	*/

void	token_redir_in(t_token **token_lst, t_malloc **lst_malloc)
{
	if (!token_lst)
		return ;
	create_token (ft_strdup ("<", lst_malloc), REDIR_IN, lst_malloc, token_lst);
}

/*	=====================================================	*/

void	init_value(bool *in_squote, bool *in_dquote, int *i)
{
	if (!in_squote || !in_dquote || !i)
		return ;
	(*in_squote) = false;
	(*in_dquote) = false;
	(*i) = 0;
}

/*	=====================================================	*/