/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: w <w@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:28:38 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/25 18:48:08 by w                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
void	token_redir_out(t_token **token_lst, t_malloc **lst_malloc)
{
	if (!token_lst || !lst_malloc)
		return ;
	create_token (ft_strdup (">", lst_malloc),
		REDIR_OUT, lst_malloc, token_lst);
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
void	token_redir_heredoc(t_token **token_lst, t_malloc **lst_malloc)
{
	if (!token_lst || !lst_malloc)
		return ;
	create_token (ft_strdup ("<<", lst_malloc), HEREDOC, lst_malloc, token_lst);
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
void	handle_redir_case(char **line, t_token **lst_token,
	t_malloc **lst_malloc)
{
	if (!line || !lst_token || !lst_malloc)
		return ;
	else if (is_redir_in (**line))
	{
		if (*(*line + 1) == '\0' || !is_here_doc (line))
			return (token_redir_in (lst_token, lst_malloc));
		else
		{
			token_redir_heredoc (lst_token, lst_malloc);
			(*line)++;
		}
	}
	else if (is_redir_out (**line))
	{
		if (*(*line + 1) == '\0' || !is_append (line))
			return (token_redir_out (lst_token, lst_malloc));
		else
		{
			token_append (lst_token, lst_malloc);
			(*line)++;
		}
	}
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
void	token_operator(char **line, t_token **lst_token, t_malloc **lst_malloc)
{
	if (!lst_token || !lst_malloc)
		return ;
	else if (is_pipe (**line))
		token_pipe (lst_token, lst_malloc);
	else if (is_redir_in (**line) || is_redir_out (**line))
		handle_redir_case(line, lst_token, lst_malloc);
	else
		return ;
}

/*	=====================================================	*/

/*	Carre on revient pas dessus	*/
void	token_append(t_token **token_lst, t_malloc **lst_malloc)
{
	if (!token_lst || !lst_malloc)
		return ;
	create_token (ft_strdup (">>", lst_malloc), APPEND, lst_malloc, token_lst);
}

/*	=====================================================	*/