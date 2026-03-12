/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:28:44 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/07 18:18:10 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE
}					t_node_type;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_node
{
	pid_t			pid;
	int				status;
	char			*path;
	t_node_type		type;
	char			**argv;
	t_redir			*redirs;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_env
{
	int				count;
	int				i;
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	t_env			*env;
	int				last_status;
	int				in_pipe;
	char			**envp_array;
}					t_shell;

typedef struct s_vars
{
	char			*path_env;
	char			**paths;
	char			*tmp_path;
	char			*path;
	int				i;
}					t_vars;

#endif