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

	tmp = ft_lstnew(str);
	ft_lstadd_back(ptr, tmp);
}

void	ft_lstdel(t_list *lst)
{
	if (lst)
		free(lst->str);
	free(lst);
	lst = NULL;
}
