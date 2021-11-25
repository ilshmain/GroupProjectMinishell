/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:55:52 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:55:53 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dsst;
	size_t	srrc;
	size_t	b;

	if (!dst && !src)
		return (0);
	dsst = ft_strlen(dst);
	srrc = ft_strlen(src);
	b = 0;
	if (dsst >= dstsize)
		return (srrc + dstsize);
	else
	{
		while (src[b] && dsst + b < dstsize - 1)
		{
			dst[dsst + b] = src[b];
			b++;
		}
		dst[dsst + b] = '\0';
	}
	return (dsst + srrc);
}
