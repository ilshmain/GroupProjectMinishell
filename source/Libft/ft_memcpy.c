/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:48:58 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:56:59 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*s;
	const unsigned char	*s1;
	size_t				k;

	s = dst;
	s1 = src;
	k = 0;
	if (s == NULL && s1 == NULL)
		return (0);
	while (k < n)
	{
		s[k] = s1[k];
		k++;
	}
	return (s);
}
