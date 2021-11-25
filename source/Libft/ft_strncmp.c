/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:50:00 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:50:02 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *p1, const char *p2, size_t n)
{
	size_t	k;

	k = 0;
	if (n == 0)
		return (0);
	while (k < n - 1)
	{
		if (p1[k] == '\0' && p2[k] == '\0')
			return (0);
		if ((p1[k] - p2[k]) == 0)
			k++;
		else
			break ;
	}
	return ((unsigned char)p1[k] - (unsigned char)p2[k]);
}
