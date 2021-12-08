/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:32:22 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:32:24 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_export(t_list **ptr, char *str)
{
	t_list	*tmp;
	char	*new_str;

	new_str = ft_strdup(str);
	tmp = ft_lstnew(new_str);
	ft_lstadd_back(ptr, tmp);
}

void	ft_lstdel(t_list *lst)
{
	if (lst)
		free(lst->str);
	free(lst);
	lst = NULL;
}

int	check_export(char *str, t_list *ptr)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	while (ptr)
	{
		if (!ft_strncmp(str, ptr->str, i))
		{
			free(ptr->str);
			ptr->str = ft_strdup(str);
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

void	dop_func_export(t_list *ptr, t_gnrl *zik)
{
	int	i;

	i = 1;
	while (zik->cmd->command_array[i])
	{
		if (check_export(zik->cmd->command_array[i], zik->ptr) == 1)
			return ;
		if (checking_validity_string(zik->cmd->command_array[i]) != 0)
		{
			print_error_func("minishell$: export: ", \
			zik->cmd->command_array[i]);
		}
		else
		{
			if (ft_strchr(zik->cmd->command_array[i], '=') != 0)
				add_export(&ptr, zik->cmd->command_array[i]);
		}
		i++;
	}
}
