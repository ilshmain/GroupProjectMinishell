/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:03:22 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 14:03:23 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_strnstr_ms(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen_ms(str2) == 0)
		return ((char *)str1);
	while (str1[0] != '\0' != 0 && (i + j < len && str1[i]))
	{
		if (str1[i + j] == str2[j])
		{
			j++;
			if (str2[j] == '\0')
				return ((char *)str1 + i);
		}
		else
		{
			i++;
			j = 0;
		}
	}
	return (0);
}
