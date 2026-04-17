/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_minishell2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 10:07:38 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/17 07:54:43 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	====================================================	*/


void	clean_history_malloc_shell(t_shell *shell, t_malloc **lst_malloc)
{
	clean_lst_malloc (lst_malloc);
	(*lst_malloc) = NULL;
	clean_shell(shell);
	rl_clear_history();
}

/*	====================================================	*/

void	clean_line(char *line)
{
	if (!line)
		return ;
	else
		free (line);
}
/*	====================================================	*/
