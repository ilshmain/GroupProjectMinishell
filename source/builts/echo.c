/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:31:43 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:31:46 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	size_two_poineter_mas(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	line_break(t_gnrl *zik, int i, int k)
{
	if (i == 2)
		ft_putstr_fd("", STDOUT_FILENO);
	else
	{
		while (ft_strcmp(zik->cmd->command_array[k], "-n") == 0)
			k++;
		if (k == i)
			ft_putstr_fd("", STDOUT_FILENO);
		else
		{
			while (zik->cmd->command_array[k + 1])
			{
				ft_putstr_fd(zik->cmd->command_array[k], STDOUT_FILENO);
				ft_putstr_fd(" ", STDOUT_FILENO);
				k++;
			}
			ft_putstr_fd(zik->cmd->command_array[k], STDOUT_FILENO);
		}
	}
}

int	echo_built(t_gnrl *zik)
{
	int	i;
	int	k;

	k = 1;
	i = size_two_poineter_mas(zik->cmd->command_array);
	if (i == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (ft_strcmp(zik->cmd->command_array[1], "-n") == 0)
		line_break(zik, i, k);
	else
	{
		while (zik->cmd->command_array[k])
		{
			ft_putstr_fd(zik->cmd->command_array[k], STDOUT_FILENO);
			ft_putstr_fd(" ", STDOUT_FILENO);
			k++;
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	exit_code = 0;
	return (1);
}