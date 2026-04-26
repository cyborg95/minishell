/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:28:44 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/26 09:58:55 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define EXIT "exit"
# define PROMPT "minishell> "
# include "minishell.h"
# include <stdbool.h>

/*	================	EXECUTION STRUCT	================	*/

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE
}						t_node_type;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}						t_redir_type;

typedef struct s_redir
{
	int					fd;
	int					expand;
	t_redir_type		type;
	char				*file;
	struct s_redir		*next;
}						t_redir;

typedef struct s_node
{
	pid_t				pid;
	int					status;
	char				*path;
	t_node_type			type;
	char				**argv;
	t_redir				*redirs;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	t_env				*env;
	int					last_status;
	int					should_exit;
	int					in_pipe;
	char				**envp_array;
	int					stdin_backup;
	int					stdout_backup;
	char				*cmd_from_args;
	int					is_interactive;
}						t_shell;

typedef struct s_vars
{
	char				*path_env;
	char				**paths;
	char				*tmp_path;
	char				*path;
	int					i;
}						t_vars;

/*	================	PARSING STRUCT	================	*/

typedef struct s_token	t_token;
typedef struct s_malloc	t_malloc;
typedef struct s_cmd	t_cmd;

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	EXPAND
}						t_type;

struct					s_token
{
	char				*word;
	t_type				type;
	t_token				*next;
};

struct					s_malloc
{
	void				*adress_malloc;
	t_malloc			*next;
};

struct					s_cmd
{
	char				**args;
	t_redir				*redir;
	t_cmd				*next;
};

typedef struct s_word_state
{
	char				**line;
	char				*word;
	int					i;
	bool				in_squote;
	bool				in_dquote;
}						t_word_state;

typedef struct s_exec_ctx
{
	char				**argv;
	t_shell				*shell;
}						t_exec_ctx;

typedef struct s_expand
{
	int		i;
	char	*result;
	char	*tmp;
	char	*old;
	char	*value;
	char	*var;
	int		in_single_quote;
	int		in_double_quote;
}	t_expand;
#endif
