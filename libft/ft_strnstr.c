/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:39:26 by otidahoh          #+#    #+#             */
/*   Updated: 2025/11/12 11:22:17 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (*little == '\0')
	{
		return ((char *)&big[i]);
	}
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && little[j]
			&& big[i + j] == little[j] && (i + j) < len)
		{
			j++;
		}
		if (little[j] == '\0')
		{
			return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>

int main(void)
{
            const char *largestring = "Foo Bar Baz";
            const char *smallstring = "Bar";
            char *ptr;

            ptr = ft_strnstr(largestring, smallstring, 10);
            printf("%s\n", ptr);
            return (0);
}*/
