/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:03:20 by otidahoh          #+#    #+#             */
/*   Updated: 2026/04/02 17:28:58 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_with_escapes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\\')
		{
			i++;
			if (s[i] == 'n')
				write(1, "\n", 1);
			else if (s[i] == 't')
				write(1, "\t", 1);
			else if (s[i] == '\\')
				write(1, "\\", 1);
			else
				write(1, &s[i], 1);
		}
		else
			write(1, &s[i], 1);
		i++;
	}
}

int	is_valid_flag(char *arg)
{
	int	j;

	if (arg[0] != '-' || !arg[1])
		return (0);
	j = 1;
	while (arg[j])
	{
		if (arg[j] != 'n' && arg[j] != 'e')
			return (0);
		j++;
	}
	return (1);
}

int	builtin_echo(char **argv)
{
	int i;
	int j;
	int nl;
	int interpret;

	i = 1;
	nl = 1;
	interpret = 0;
	while (argv[i] && is_valid_flag(argv[i]))
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] == 'n')
				nl = 0;
			else if (argv[i][j] == 'e')
				interpret = 1;
			j++;
		}
		i++;
	}
	while (argv[i])
	{
		if (interpret)
			print_with_escapes(argv[i]);
		else
			printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}
