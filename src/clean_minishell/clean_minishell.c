/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 10:06:47 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/13 10:14:22 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	====================================================	*/

void	bypass_ac_av(int *argc, char **argv)
{
	(void)argc;
	(void)argv;
}

/*	====================================================	*/

void	init_shell_maloc_lst(t_malloc **malloc_lst, t_shell *shell, char **envp)
{
	(*malloc_lst) = NULL;
	shell->env = init_env(envp);
	shell->envp_array = env_list_to_array(shell->env);
	shell->last_status = 0;
}

/*	====================================================	*/

void	gestionnaire_signaux(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

/*	====================================================	*/

void	clean_and_new_lstmalloc(t_malloc *lst_malloc)
{
	clean_lst_malloc(lst_malloc);
	lst_malloc = NULL;
}

/*	====================================================	*/

void	clean_shell(t_shell *shell)
{
	ft_free_tab(shell->envp_array);
	free_env_list(shell->env);
}

/*	====================================================	*/