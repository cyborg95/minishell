/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ustils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:23:33 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/23 16:43:17 by otidahoh         ###   ########.fr       */
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
