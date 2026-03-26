/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: w <w@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:01:58 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/25 18:50:51 by w                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	

Dans le cas des multilignes, si la ligne fini par un backslah 
alors il n'ya pas d espace qui seprare ce qu suit

Si la ligne finit par un pipe ou il manque une quote, alors il faudra un espace 

*/
#include "minishell.h"

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
	else if (is_double_quote (c) && *in_squote == false)
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
	next_line = remix_readline ("> ", lst_malloc);
	if (!next_line)
		return ;
	if (ends_with_backslash (*line))
	{
		(*line)[strlen(*line) - 1] = '\0';
		tmp2 = ft_strjoin (*line, "", lst_malloc);
	}
	else
		tmp2 = ft_strjoin (*line, " ", lst_malloc);
	tmp = ft_strjoin (tmp2, next_line, lst_malloc);
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
		if (is_quote(**line) &&
			((**line == '\'' && !in_dquote)
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