/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:05:01 by otidahoh          #+#    #+#             */
/*   Updated: 2025/11/12 16:10:51 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	dl;
	size_t	sl;

	i = 0;
	dl = 0;
	sl = 0;
	while (dst[dl] && dl < siz)
		dl++;
	while (src[sl])
		sl++;
	if (dl >= siz)
		return (sl + siz);
	while (src[i] && (dl + i + 1) < siz)
	{
		dst[dl + i] = src[i];
		i++;
	}
	dst[dl + i] = '\0';
	return (dl + sl);
}
