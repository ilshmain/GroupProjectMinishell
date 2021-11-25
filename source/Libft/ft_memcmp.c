/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:54:58 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:54:59 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			k;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	k = 0;
	while (k < n)
	{
		if ((p1[k] - p2[k]) == 0)
			k++;
		else
			return (p1[k] - p2[k]);
	}
	return (0);
}
