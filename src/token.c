/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:51:44 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/14 17:51:07 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	================================================================	*/

/*
struct s_token
{
	char	*word;
	t_type	type;
	t_token	*next;
};
*/

/*	================================================================	*/

void	clean_token(t_token *token_lst)
{
	t_token	*next_token;

	next_token = NULL;
	if (!token_lst)
		return ;
	while (token_lst)
	{
		next_token = token_lst->next;
		free (token_lst->word);
		token_lst->word = NULL;
		token_lst = next_token;
	}
	return ;
}

/*	================================================================	*/

t_token	*create_token(t_token *token_lst, char *word, int type)
{
	t_token	*token;

	if (!token_lst)
		return (NULL);
	token = malloc (sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->type = type;
	token->word = word;
	return (token);
}

/*	================================================================	*/

void	add_back_token_lst(t_token *token_lst, t_token *token)
{
	t_token	*tmp;

	if (!token_lst || !token)
		return ;
	tmp = token_lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = token;
	return ;
}

/*	================================================================	*/