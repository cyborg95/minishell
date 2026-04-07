/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:12:00 by otidahoh          #+#    #+#             */
/*   Updated: 2025/11/12 11:20:21 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		c;
	long int	ln;

	ln = n;
	if (ln < 0)
	{
		write (fd, "-", 1);
		ln *= -1;
	}
	if (ln >= 10)
	{
		ft_putnbr_fd(ln / 10, fd);
	}
	c = (ln % 10) + '0';
	write (fd, &c, 1);
}
