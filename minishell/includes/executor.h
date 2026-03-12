/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:43:32 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/04 16:18:45 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "structs.h"

int		executor(t_node *root, t_shell *shell);
int		execute_node(t_node *node, t_shell *shell);
int		execute_pipe(t_node *node, t_shell *shell);
int		execute_command(t_node *node, t_shell *shell);
int		execute_external(t_node *node, t_shell *shell);
void	apply_redirections(t_redir *redir);

#endif