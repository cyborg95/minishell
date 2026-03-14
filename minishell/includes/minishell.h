/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:44:15 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/14 15:10:40 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "builtins.h"
# include "executor.h"
# include "structs.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

t_env		*init_env(char **envp);
char		**env_list_to_array(t_env *env);
void		ft_free_tab(char **tab);
void		free_env_list(t_env *env);
int			ft_strcmp(const char *s1, const char *s2);
void		add_or_update_env(t_shell *shell, char *key, char *value);
char		*my_getenv(char *name, char **env);
void		handle_signal(int sig);
void		handle_signal2(int sig);
void		expand_tree(t_node *node, t_shell *shell);
int			is_valid_identifier(char *str);
int			printable_export(t_shell *shell);

extern int	g_signal;

#endif