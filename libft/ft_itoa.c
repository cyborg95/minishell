/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:05:19 by otidahoh          #+#    #+#             */
/*   Updated: 2025/11/13 11:55:17 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbcount(long int c)
{
	int	count;

	count = 0;
	if (c <= 0)
		count = 1;
	else
		count = 0;
	while (c)
	{
		c /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long		nb;
	int			len;
	char		*str;

	nb = n;
	len = ft_nbcount(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}
