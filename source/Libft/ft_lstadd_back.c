/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:51:50 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:51:52 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ending;

	if (!lst)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{	
		ending = ft_lstlast(*lst);
		ending->next = new;
	}
}
