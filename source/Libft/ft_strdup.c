/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:49:35 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:49:37 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		k;
	char	*buf;

	k = 0;
	while (s1[k])
		k++;
	buf = (char *)malloc(k + 1);
	if (buf == NULL)
		return (NULL);
	k = 0;
	while (s1[k])
	{
		buf[k] = s1[k];
		k++;
	}
	buf[k] = '\0';
	return (buf);
}
