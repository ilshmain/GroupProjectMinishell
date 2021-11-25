/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:50:14 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:50:16 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	k;
	size_t	j;
	size_t	p;

	k = 0;
	p = 0;
	if (!s1)
		return (NULL);
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[k]) && s1[k])
		k++;
	while (ft_strchr(set, s1[j - 1]) && j > k)
		j--;
	str = (char *)malloc(j - k + 1);
	if (!str)
		return (NULL);
	while (k < j)
		str[p++] = s1[k++];
	str[p] = '\0';
	return (str);
}
