/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:53:10 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:53:12 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	k;
	size_t	p;
	char	*buf;

	if (!s1 || !s2)
		return (0);
	k = -1;
	p = 0;
	buf = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!buf)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	while (s1[++k])
		buf[k] = s1[k];
	while (s2[p])
	{
		buf[k] = s2[p];
		k++;
		p++;
	}
	buf[k] = '\0';
	return (buf);
}
