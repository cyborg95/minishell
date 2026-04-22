/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 10:06:47 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/22 10:46:06 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	====================================================	*/

void	bypass_ac_av(int *argc, char **argv, t_shell *shell)
{
	(void)argc;
	(void)argv;
	shell->should_exit = 0;
	shell->last_status = 0;
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

void	clean_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free_env_list(shell->env);
	if (shell->envp_array)
		ft_free_tab(shell->envp_array);
}

/*	====================================================	*/