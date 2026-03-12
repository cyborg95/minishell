/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:57:50 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/04 15:07:03 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_cd(char **argv, t_shell *shell)
{
	char	oldpwd[1024];
	char	newpwd[1024];
	char	*path;

	if (!getcwd(oldpwd, sizeof(oldpwd)))
		return (perror("cd"), 1);
	if (!argv[1] || argv[1][0] == '\0')
		path = my_getenv("HOME", shell->envp_array);
	else if (ft_strcmp(argv[1], "-") == 0)
		path = my_getenv("OLDPWD", shell->envp_array);
	else
		path = argv[1];
	if (!path || chdir(path) == -1)
		return (perror("cd"), 1);
	if (!getcwd(newpwd, sizeof(newpwd)))
		return (perror("cd"), 1);
	add_or_update_env(shell, "OLDPWD", oldpwd);
	add_or_update_env(shell, "PWD", newpwd);
	ft_free_tab(shell->envp_array);
	shell->envp_array = env_list_to_array(shell->env);
	shell->last_status = 0;
	return (0);
}
