/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:04:31 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/24 19:27:10 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_expand(t_expand *e)
{
	e->i = 0;
	e->in_sq = 0;
	e->in_dq = 0;
	e->result = strdup("");
}

static void	handle_quotes(char c, t_expand *e)
{
	if (c == '\'' && !e->in_dq)
		e->in_sq = !e->in_sq;
	else if (c == '"' && !e->in_sq)
		e->in_dq = !e->in_dq;
	else
		return ;
	e->i++;
}

static char	*handle_dollar(char *arg, t_expand *e, t_shell *shell)
{
	char	*var;
	char	*value;

	e->i++;
	if (arg[e->i] == '?')
	{
		e->tmp = ft_itoa_remix(shell->last_status);
		e->i++;
	}
	else if (ft_isalpha(arg[e->i]) || arg[e->i] == '_')
	{
		var = extract_var(arg, &e->i);
		value = get_env_value(shell->env, var);
		if (value)
			e->tmp = strdup(value);
		else
			e->tmp = strdup("");
		free(var);
	}
	else
		e->tmp = strdup("$");
	return (e->tmp);
}

char	*expand_var(char *arg, t_shell *shell)
{
	t_expand	e;

	init_expand(&e);
	while (arg[e.i])
	{
		handle_quotes(arg[e.i], &e);
		if (!arg[e.i])
			break ;
		if (arg[e.i] == '$' && !e.in_sq)
			e.tmp = handle_dollar(arg, &e, shell);
		else
		{
			e.tmp = ft_substr_remix(arg, e.i, 1);
			e.i++;
		}
		e.old = e.result;
		e.result = ft_1strjoin(e.result, e.tmp);
		free(e.old);
		free(e.tmp);
	}
	return (e.result);
}

/*char	*expand_var(char *arg, t_shell *shell)
{
	int		i;
	char	*result;
	char	*tmp;
	char	*old;
	char	*value;
	char	*var;
	int		in_single_quote;
	int		in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	result = strdup("");
	while (arg[i])
	{
		if (arg[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			i++;
			continue ;
		}
		else if (arg[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			i++;
			continue ;
		}
		else if (arg[i] == '$' && !in_single_quote)
		{
			i++;
			if (arg[i + 1] == '"' || arg[i + 1] == '\'')
			{
				tmp = strdup("");
				i++;
			}
			else if (arg[i] == '?')
			{
				tmp = ft_itoa_remix(shell->last_status);
				i++;
			}
			else if (ft_isalpha(arg[i]) || arg[i] == '_')
			{
				var = extract_var(arg, &i);
				value = get_env_value(shell->env, var);
				if (value)
					tmp = strdup(value);
				else
					tmp = strdup("");
				free(var);
			}
			else
			{
				tmp = strdup("$");
			}
		}
		else
		{
			tmp = ft_substr_remix(arg, i, 1);
			i++;
		}
		old = result;
		result = ft_1strjoin(result, tmp);
		free (old);
		free (tmp);
	}
	return (result);
}*/
