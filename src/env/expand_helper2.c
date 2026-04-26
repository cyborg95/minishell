/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:04:31 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/26 09:59:41 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(char c, t_expand *exp)
{
	if (c == '\'' && !exp->in_double_quote)
	{
		exp->in_single_quote = !exp->in_single_quote;
		exp->i++;
		return (1);
	}
	else if (c == '"' && !exp->in_single_quote)
	{
		exp->in_double_quote = !exp->in_double_quote;
		exp->i++;
		return (1);
	}
	return (0);
}

char	*handle_dollar(char *arg, t_expand *exp, t_shell *shell)
{
	char	*tmp;

	if (!arg[exp->i])
		return (ft_1strdup("$"));
	else if (arg[exp->i] == '?')
	{
		tmp = ft_itoa_remix(shell->last_status);
		exp->i++;
		return (tmp);
	}
	else if (ft_isalpha(arg[exp->i]) || arg[exp->i] == '_')
	{
		exp->var = extract_var(arg, &exp->i);
		exp->value = get_env_value(shell->env, exp->var);
		if (exp->value)
			tmp = strdup(exp->value);
		else
			tmp = ft_1strdup("");
		free(exp->var);
		return (tmp);
	}
	else if ((arg[exp->i] == '"' || arg[exp->i] == '\'')
		&& !exp->in_double_quote)
		return (ft_1strdup(""));
	return (ft_1strdup("$"));
}

void	append_tmp(t_expand *exp)
{
	exp->old = exp->result;
	exp->result = ft_1strjoin(exp->result, exp->tmp);
	free(exp->old);
	free(exp->tmp);
}

char	*expand_var(char *arg, t_shell *shell)
{
	t_expand	exp;

	exp.i = 0;
	exp.in_single_quote = 0;
	exp.in_double_quote = 0;
	exp.result = ft_1strdup("");
	while (arg[exp.i])
	{
		if (handle_quotes(arg[exp.i], &exp))
			continue ;
		else if (arg[exp.i] == '$' && !exp.in_single_quote)
		{
			exp.i++;
			exp.tmp = handle_dollar(arg, &exp, shell);
		}
		else
		{
			exp.tmp = ft_substr_remix(arg, exp.i, 1);
			exp.i++;
		}
		append_tmp(&exp);
	}
	return (exp.result);
}
