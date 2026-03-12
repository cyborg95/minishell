/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:03:20 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/11 15:59:18 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(char **argv)
{
	int	i;
	int	j;
	int	nl;

	nl = 1;
	i = 1;
	while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break ;
		nl = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (0);
}
