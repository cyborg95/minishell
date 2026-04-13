/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_minishell2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 10:07:38 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/13 10:08:13 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	====================================================	*/


void	clean_history_malloc_shell(t_shell *shell, t_malloc *lst_malloc)
{
	clean_and_new_lstmalloc(lst_malloc);
	clean_shell(shell);
	rl_clear_history();
}

/*	====================================================	*/

void	clean_line(char *line, t_malloc *malloc_lst)
{
	free_remix(line, &malloc_lst);
	line = NULL;
}
/*	====================================================	*/
