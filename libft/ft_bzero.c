/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:10:07 by otidahoh          #+#    #+#             */
/*   Updated: 2025/11/12 11:17:26 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t				i;
	unsigned char		*bz;

	bz = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		bz[i] = 0;
		i++;
	}
}
