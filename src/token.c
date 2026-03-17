/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:51:44 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/17 14:04:42 by wngambi          ###   ########.fr       */
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

void	clean_token(t_token **token_lst)
{
	t_token	*tmp;

	if (!token_lst || !(*token_lst))
		return ;
	while (*token_lst)
	{
		tmp = (*token_lst)->next;
		free ((*token_lst)->word);
		(*token_lst)->word = NULL;
		(*token_lst)->next = NULL;
		free ((*token_lst));
		*token_lst = tmp;
	}
	(*token_lst) = NULL;
}

/*	================================================================	*/

void	add_back_token_lst(t_token **token_lst, t_token *token)
{
	t_token	*tmp;

	if (!token_lst || !token)
		return ;
	tmp = *token_lst;
	if ((*token_lst) == NULL)
		(*token_lst) = token;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = token;
	}
	return ;
}

/*	================================================================	*/

t_token	*create_token(char *word, int type,
	t_malloc **lst_malloc, t_token **token_lst)
{
	t_token	*token;

	if (!word || !lst_malloc)
		return (NULL);
	token = malloc_remix (sizeof(t_token), lst_malloc);
	token->next = NULL;
	token->type = type;
	token->word = word;
	add_back_token_lst (token_lst, token);
	return (token);
}

/*	================================================================	*/

void	display_token(t_token *token_lst)
{
	int	i;

	if (!token_lst)
		return ;
	i = 0;
	while (token_lst)
	{
		++i;
		printf ("Token numero %d\n\tWord: %s\n\tType: %d\n\t Adresse: %p\n", i,
			token_lst->word, token_lst->type, token_lst);
		token_lst = token_lst->next;
	}
}

/*	================================================================	*/