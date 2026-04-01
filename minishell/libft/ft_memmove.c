/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:10:04 by otidahoh          #+#    #+#             */
/*   Updated: 2025/11/13 16:05:04 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t					i;
	unsigned char			*dt;
	const unsigned char		*sc;

	dt = (unsigned char *)dest;
	sc = (const unsigned char *)src;
	i = 0;
	if (src == NULL && dest == NULL)
		return (NULL);
	if (dt > sc)
	{
		while (n-- > 0)
		{
			dt[n] = sc[n];
		}
	}
	else
	{
		while (i < n)
		{
			dt[i] = sc[i];
			i++;
		}
	}
	return (dest);
}
