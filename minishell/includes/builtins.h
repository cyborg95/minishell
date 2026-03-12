/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:42:10 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/07 17:30:03 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

int		is_builtin(const char *cmd);
int		execute_builtin(t_node *node, t_shell *shell);

int		builtin_echo(char **argv);
int		builtin_cd(char **argv, t_shell *shell);
int		builtin_pwd(void);
int		builtin_export(char **argv, t_shell *shell);
int		builtin_unset(char **argv, t_shell *shell);
int		builtin_env(t_env *env);
void	builtin_exit(char **argv, t_shell *shell);

#endif