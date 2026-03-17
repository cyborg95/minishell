/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:12:13 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/17 11:03:21 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
struct s_malloc
{
	void		*adress_malloc;
	t_malloc	*next;
};
*/

/*	===================================================================	*/

void	clean_lst_malloc(t_malloc *lst_malloc)
{
	t_malloc	*next_malloc;

	next_malloc = NULL;
	if (!lst_malloc)
		return ;
	while (lst_malloc != NULL)
	{
		next_malloc = lst_malloc->next;
		free (lst_malloc->adress_malloc);
		lst_malloc->next = NULL;
		lst_malloc = next_malloc;
	}
	return ;
}

/*	===================================================================	*/

t_malloc	*create_node_malloc(void *address_malloc)
{
	t_malloc	*node;

	node = malloc (sizeof(t_malloc));
	if (!node)
		return (NULL);
	node->adress_malloc = address_malloc;
	node->next = NULL;
	return (node);
}

/*	===================================================================	*/

void	add_malloc_in_lst(t_malloc **lst_malloc, t_malloc *malloc_node)
{
	t_malloc	*tmp;

	if (!lst_malloc || !(*lst_malloc) || !malloc_node)
		return ;
	tmp = *lst_malloc;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = malloc_node;
}

/*	===================================================================	*/

void	*malloc_remix(size_t nb_octets, t_malloc **lst_malloc)
{
	void		*link;
	t_malloc	*malloc_node;

	link = malloc(nb_octets);
	if (!link)
	{
		perror ("Malloc: ");
		clean_lst_malloc (*lst_malloc);
		exit (1);
	}
	malloc_node = create_node_malloc (link);
	if (!malloc_node)
	{
		perror ("Create_node_malloc: ");
		clean_lst_malloc (*lst_malloc);
		exit (1);
	}
	add_malloc_in_lst (lst_malloc, malloc_node);
	return (link);
}
