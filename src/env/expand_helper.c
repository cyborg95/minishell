/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:23:03 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/03 16:00:24 by otidahoh         ###   ########.fr       */
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

char	*ft_substr_remix(char *s, unsigned int start, size_t len,
		t_malloc **malloc_lst)
{
	char	*sub;
	size_t	i;

	sub = malloc_remix(len + 1, malloc_lst);
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
	free(ptr);
	*malloc_lst = remove_from_list(*malloc_lst, ptr);
}

char	*extract_var(char *arg, int *i, t_malloc **malloc_lst)
{
	int	start;

	start = *i;
	while (ft_isalpha(arg[*i]) || ft_isdigit(arg[*i]) || arg[*i] == '_')
		(*i)++;
	return (ft_substr_remix(arg, start, *i - start, malloc_lst));
}

char	*expand_var(char *arg, t_shell *shell, t_malloc **malloc_lst)
{
	int		i;
	char	*result;
	char	*tmp;
	char	*old;
	char	*value;
	char	*var;
	char	quote;

	i = 0;
	result = ft_strdup("", malloc_lst);
	while (arg[i])
	{
		if (arg[i] == '\x01')
		{
			tmp = ft_strdup("$", malloc_lst);
			i++;
		}
		else if (arg[i] == '$')
		{
			i++;
			if (!arg[i])
				tmp = ft_strdup("", malloc_lst);
			else if (arg[i] == '"' || arg[i] == '\'')
			{
				quote = arg[i++];
				if (arg[i] == quote)
					i++;
				tmp = ft_strdup("", malloc_lst);
			}
			else if (arg[i] == '?')
			{
				tmp = ft_itoa_remix(shell->last_status, malloc_lst);
				i++;
			}
			else if (!ft_isalpha(arg[i]) && arg[i] != '_')
			{
				tmp = ft_strdup("", malloc_lst);
				i++;
			}
			else
			{
				var = extract_var(arg, &i, malloc_lst);
				value = get_env_value(shell->env, var);
				if (value)
					tmp = ft_strdup(value, malloc_lst);
				else
					tmp = ft_strdup("", malloc_lst);
			}
		}
		else
		{
			tmp = ft_substr_remix(arg, i, 1, malloc_lst);
			i++;
		}
		old = result;
		result = ft_strjoin(result, tmp, malloc_lst);
		free_remix(old, malloc_lst);
		free_remix(tmp, malloc_lst);
	}
	return (result);
}
