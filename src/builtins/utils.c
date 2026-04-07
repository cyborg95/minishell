/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otidahoh <otidahoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:15:21 by otidahoh          #+#    #+#             */
/*   Updated: 2026/03/14 15:10:05 by otidahoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_identifier(char *str)
{
	int	in;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	in = 1;
	while (str[in] && str[in] != '=')
	{
		if (!ft_isalnum(str[in]) && str[in] != '_')
			return (0);
		in++;
	}
	return (1);
}

int	printable_export(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	return (0);
}
