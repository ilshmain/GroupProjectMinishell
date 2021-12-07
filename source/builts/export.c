/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:32:12 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:32:15 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Export Built
int	dop_sortirovka(t_list **list)
{
	char	*str;
	char	*tmp;
	t_list	*lst;
	int		flag;

	flag = 1;
	lst = *list;
	while ((lst->next != NULL) && (lst->next))
	{
		if (ft_strcmp(lst->str, (lst->next)->str) > 0)
		{
			tmp = ft_strdup((lst->next)->str);
			str = ft_strdup(lst->str);
			free(lst->str);
			free((lst->next)->str);
			lst->str = ft_strdup(tmp);
			(lst->next)->str = ft_strdup(str);
			free(str);
			free(tmp);
			flag--;
		}
		lst = lst->next;
	}
	return (flag);
}

void	sort_alphabet(t_list **sortMas)
{
	t_list	*lst;
	int		flag;

	while (1)
	{
		lst = *sortMas;
		flag = dop_sortirovka(&lst);
		if (flag == 1)
			break ;
	}
}

void	print_sortmas(t_list **sortMas)
{
	t_list	*new;

	while (*sortMas)
	{
		new = (*sortMas)->next;
		if (ft_strncmp("_=", (*sortMas)->str, 2) != 0)
		{
			if (ft_strcmp("OLDPWD=", (*sortMas)->str) == 0)
				ft_putstr_fd("declare -x OLDPWD\n", STDOUT_FILENO);
			else
			{
				ft_putstr_fd("declare -x ", STDOUT_FILENO);
				ft_putendl_fd((*sortMas)->str, STDOUT_FILENO);
			}
		}
		ft_lstdel(*sortMas);
		*sortMas = new;
	}
}

void	print_export(t_list *ptr, t_list **sortMas)
{
	t_list	*tmp;
	char	*dop_str;

	*sortMas = NULL;
	while (ptr)
	{
		dop_str = ft_strdup(ptr->str);
		tmp = ft_lstnew(dop_str);
		ft_lstadd_back(sortMas, tmp);
		ptr = ptr->next;
	}
	sort_alphabet(sortMas);
	print_sortmas(&(*sortMas));
}

int	export_built(t_list *ptr, t_gnrl *zik)
{
	int		i;
	t_list	*sort_mas;

	i = 0;
	g_exit_code = 0;
	while (zik->cmd->command_array[i])
		i++;
	if (i == 1)
		print_export(ptr, &sort_mas);
	else
		dop_func_export(ptr, zik);
	return (1);
}
//**************************************