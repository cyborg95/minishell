/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:23:03 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/20 18:49:43 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_malloc	*remove_from_list(t_malloc *lst, void *ptr)
{
	t_malloc	*tmp;
	t_malloc	*prev;

	tmp = lst;
	prev = NULL;
	while (tmp)
	{
		if (tmp->adress_malloc == ptr)
		{
			if (prev)
				prev->next = tmp->next;
			else
				lst = tmp->next;
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (lst);
}

char	*ft_substr_remix(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	sub = malloc (len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

void	free_remix(void *ptr, t_malloc **malloc_lst)
{
	if (!ptr)
		return ;
	*malloc_lst = remove_from_list(*malloc_lst, ptr);
	free(ptr);
}

char	*extract_var(char *arg, int *i)
{
	int	start;

	start = *i;
	while (ft_isalpha(arg[*i]) || ft_isdigit(arg[*i]) || arg[*i] == '_')
		(*i)++;
	return (ft_substr_remix(arg, start, *i - start));
}

char	*expand_var(char *arg, t_shell *shell)
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
}
