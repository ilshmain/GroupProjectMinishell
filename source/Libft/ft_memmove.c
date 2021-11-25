/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:52:24 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:52:26 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char			*s;
	const unsigned char		*s1;
	size_t					k;

	s = (unsigned char *)dst;
	s1 = (unsigned char *)src;
	k = 0;
	if (s1 > s)
	{
		while (n > 0)
		{
			s[k] = s1[k];
			n--;
			k++;
		}
	}
	if (s1 < s)
	{
		while (n > 0)
		{
			s[k + n - 1] = s1[k + n - 1];
			n--;
		}
	}
	return (s);
}
