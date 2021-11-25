/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:56:04 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:56:05 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	k;
	char	*str;

	k = 0;
	if (!s || !f)
		return (NULL);
	i = ft_strlen(s);
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	while (s[k])
	{
		str[k] = (*f)((unsigned int)k, s[k]);
		k++;
	}
	str[k] = '\0';
	return (str);
}
