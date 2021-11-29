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

int check_line_break(t_gnrl *zik, int i)
{
	int	k;

	while (zik->cmd->command_array[i])
	{
		k = 0;
		if (zik->cmd->command_array[i][k] == '-' && zik->cmd->command_array[1][k + 1] == 'n')
		{
			k = 1;
			while (zik->cmd->command_array[i][k])
			{
				if (zik->cmd->command_array[i][k] != 'n')
					return (i);
				k++;
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	echo_built(t_gnrl *zik, int i, int k)
{
	int line_break;

	i = size_two_poineter_mas(zik->cmd->command_array);
	if (i == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else
	{
		line_break = check_line_break(zik, 1);
		if (line_break == 1)
		{
			while (zik->cmd->command_array[k])
			{
				ft_putstr_fd(zik->cmd->command_array[k], STDOUT_FILENO);
				ft_putstr_fd(" ", STDOUT_FILENO);
				k++;
			}
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		else
		{
			k = line_break;
			if (i == k)
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
	exit_code = 0;
	return (1);
}
