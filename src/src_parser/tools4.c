/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:41:23 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/02 14:13:18 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
bool	is_here_doc(char **line)
{
	if (!line)
		return (false);
	else
	{
		if (*(*line + 1) != '\0' && !is_redir_in (*(*line + 1)))
			return (false);
		else if (*(*line + 1) != '\0' && is_redir_in (*(*line + 1)))
			return (true);
	}
	return (false);
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
bool	is_append(char **line)
{
	if (!line)
		return (false);
	else
	{
		if (*(*line + 1) != '\0' && !is_redir_out (*(*line + 1)))
			return (false);
		else if (*(*line + 1) != '\0' && is_redir_out (*(*line + 1)))
			return (true);
	}
	return (false);
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
bool	is_redir(t_token *lst_token)
{
	if (!lst_token)
		return (false);
	else
	{
		if (lst_token->type == REDIR_IN
			|| lst_token->type == REDIR_OUT
			|| lst_token->type == HEREDOC
			|| lst_token->type == APPEND)
			return (true);
		else
			return (false);
	}
}

/*	=====================================================	*/

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

/*	=====================================================	*/

void	display_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	printf ("Liste des arguments:  ");
	while (args[i])
	{
		printf ("[%s]", args[i]);
		i++;
		if (args[i] != NULL)
			printf ("=>");
		else
			break ;
	}
	printf ("\n");
}

/*	=====================================================	*/