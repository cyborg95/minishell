/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:59:21 by otidahoh          #+#    #+#             */
/*   Updated: 2025/11/12 17:12:32 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_in(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		begin;
	size_t		end;
	char		*trimstr;

	if (!s1 || !set)
		return (NULL);
	begin = 0;
	while (*s1 && ft_in(s1[begin], set))
		begin++;
	end = ft_strlen(s1);
	while (end > begin && ft_in(s1[end - 1], set))
		end--;
	trimstr = (char *)malloc(sizeof(char) * (end - begin + 1));
	if (!trimstr)
		return (NULL);
	ft_memcpy(trimstr, s1 + begin, end - begin);
	trimstr[end - begin] = '\0';
	return (trimstr);
}
