/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wngambi <wngambi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 18:05:21 by wngambi           #+#    #+#             */
/*   Updated: 2026/03/21 19:36:19 by wngambi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	==========================================	*/

// Operationnel on revient pas dessus
int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*	==========================================	*/

// Operationnel on revient pas dessus
char	*ft_strdup(char *str, t_malloc **lst_malloc)
{
	char	*word;
	int		size;
	int		i;

	if (!str)
		return (NULL);
	size = ft_strlen (str);
	word = malloc_remix (sizeof(char) * (size + 1), lst_malloc);
	if (!word)
		return (NULL);
	i = 0;
	while (str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

/*	=======================================================================	*/

char	*ft_strjoin(char *line, char *new_line, t_malloc **lst_malloc)
{
	char	*tmp;
	int		total_size;
	int		i;
	int		j;

	if (!line && !new_line)
		return (NULL);
	else if (line && !new_line)
		return (line);
	if (!line && new_line)
		line = ft_strdup (line, lst_malloc);
	total_size = ft_strlen (line) + ft_strlen (new_line);
	tmp = malloc_remix (sizeof(char) * (total_size + 1), lst_malloc);
	i = -1;
	while (line[++i])
		tmp[i] = line[i];
	j = 0;
	while (new_line[j])
		tmp[i++] = new_line[j++];
	tmp[i] = '\0';
	return (tmp);
}

/*	=======================================================================	*/
/*
int	main(int ac, char **av)
{
	char		*tmp;
	t_malloc	*lst_malloc;

	lst_malloc = NULL;
	(void)ac;
	tmp = ft_strjoin (av[1], av[2], &lst_malloc);
	if (!tmp)
		printf ("La chaine est NULL !\n");
	else
		printf ("%s\n", tmp);
	return (0);
}
*/