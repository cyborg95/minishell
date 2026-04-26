/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 10:32:38 by wngambi           #+#    #+#             */
/*   Updated: 2026/04/26 10:32:43 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
