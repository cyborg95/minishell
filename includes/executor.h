/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:43:32 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/21 11:02:33 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "structs.h"

int		executor(t_node *root, t_shell *shell);
int		execute_node(t_node *node, t_shell *shell, t_malloc **malloc_lst);
int		execute_pipe(t_node *node, t_shell *shell, t_malloc **malloc_lst);
int		execute_command(t_node *node, t_shell *shell, t_malloc **malloc_lst);
int		execute_external(t_node *node, t_shell *shell, t_malloc **malloc_lst);
void	apply_redirections(t_redir *redir, t_shell *shell);

#endif