/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:34:15 by otidahoh          #+#    #+#             */
/*   Updated: 2025/11/12 11:19:10 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	const unsigned char		*pt;

	pt = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (pt[i] == (unsigned char)c)
		{
			return ((void *)&pt[i]);
		}
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>

int main(void)
{
    char    data[] = "abcdefg";
    char    *res = ft_memchr(data, 'e', 7);
    printf("%s\n", res);
    return (0); 
}*/
