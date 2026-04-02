/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:28:14 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/07 16:38:39 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit(char **argv, t_shell *shell)
{
	int	status;

	printf("exit\n");
	status = shell->last_status;
	if (argv[1])
	{
		if (!is_num(argv[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			_exit(2);
		}
		if (argv[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			shell->last_status = 1;
			return ;
		}
		status = ft_atoi(argv[1]);
	}
	_exit(status % 256);
}
