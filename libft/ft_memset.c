/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:28:25 by otidahoh          #+#    #+#             */
/*   Updated: 2025/11/13 16:02:21 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int val, size_t len)
{
	size_t				i;
	unsigned char		*pt;

	pt = (unsigned char *)dest;
	i = 0;
	while (i < len)
	{
		pt[i] = (unsigned char)val;
		i++;
	}
	return (dest);
}
