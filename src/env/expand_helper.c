/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:23:03 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/23 18:09:19 by otidahoh         ###   ########.fr       */
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
