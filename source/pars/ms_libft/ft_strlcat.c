/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:02:44 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 14:02:45 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

size_t	ft_strlcat_ms(char *dst, const char *src, size_t size)
{
	size_t		dsts;
	size_t		srcs;
	size_t		i;
	size_t		j;

	dsts = ft_strlen_ms(dst);
	srcs = ft_strlen_ms(src);
	i = 0;
	if (dsts >= size)
		j = srcs + size;
	else
	{
		j = dsts + srcs;
		while (src[i] && dsts < size - 1)
		{
			dst[dsts] = src[i];
			i++;
			dsts++;
		}
		dst[dsts] = '\0';
	}
	return (j);
}
