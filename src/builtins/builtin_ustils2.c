/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ustils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:23:33 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/26 10:11:04 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_wrapper(void *data)
{
	t_exec_ctx	*ctx;

	ctx = (t_exec_ctx *)data;
	return (builtin_cd(ctx->argv, ctx->shell));
}

int	echo_wrapper(void *data)
{
	return (builtin_echo((char **)data));
}

int	pwd_wrapper(void *data)
{
	(void)data;
	return (builtin_pwd());
}

int	env_wrapper(void *data)
{
	return (builtin_env((t_env *)data));
}

int	export_wrapper(void *data)
{
	t_exec_ctx	*ctx;

	ctx = (t_exec_ctx *)data;
	return (builtin_export(ctx->argv, ctx->shell));
}

int	unset_wrapper(void *data)
{
	t_exec_ctx	*ctx;

	ctx = (t_exec_ctx *)data;
	return (builtin_unset(ctx->argv, ctx->shell));
}

int	exit_wrapper(void *data)
{
	t_exec_ctx	*ctx;

	ctx = (t_exec_ctx *)data;
	builtin_exit(ctx->argv, ctx->shell);
	return (ctx->shell->last_status);
}
