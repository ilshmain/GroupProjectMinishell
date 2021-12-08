/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:32:33 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:32:35 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset_env(t_list *ptr, char *str)
{
	t_list	*tmp;

	while (ptr->next != NULL)
	{
		if (ft_strncmp(ptr->next->str, str, ft_strlen(str)) == 0)
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			free (tmp->str);
			free (tmp);
			break ;
		}
		ptr = ptr->next;
	}
}

int	dop_func_unset(char *str, int k)
{
	while (str[k])
	{
		if (str[k] == 47)
		{
			print_error_func("unset: ", str);
			return (1);
		}
		k++;
	}
	return (0);
}

int	unset_built(t_list *ptr, t_gnrl *zik, int i, int k)
{
	g_exit_code = 0;
	while (zik->cmd->command_array[i])
		i++;
	if (i != 1)
	{
		i = 1;
		while (zik->cmd->command_array[i])
		{
			if (dop_func_unset(zik->cmd->command_array[i], k) == 1)
				return (1);
			if (checking_validity_string(zik->cmd->command_array[i]) == 1)
				print_error_func("unset: ", zik->cmd->command_array[i]);
			if (ft_strchr(zik->cmd->command_array[i], '=') != 0)
				print_error_func("unset: ", zik->cmd->command_array[i]);
			unset_env(ptr, zik->cmd->command_array[i]);
			i++;
		}
	}
	return (1);
}
