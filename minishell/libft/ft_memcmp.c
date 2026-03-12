/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:13:25 by otidahoh          #+#    #+#             */
/*   Updated: 2025/11/13 16:01:57 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*pt1;
	const unsigned char	*pt2;

	pt1 = (const unsigned char *)s1;
	pt2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (pt1[i] != pt2[i])
		{
			return (pt1[i] - pt2[i]);
		}
		i++;
	}
	return (0);
}
