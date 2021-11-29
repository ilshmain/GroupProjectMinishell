/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:03:30 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 14:03:31 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_substr_ms(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen_ms(s))
		return (ft_strdup_ms(""));
	if ((start + len) < ft_strlen_ms(s))
		res = (char *)malloc(sizeof(*s) * len + 1);
	else
		res = (char *)malloc(sizeof(*s) * ft_strlen_ms(s) - start + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}
