/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:01:12 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 14:01:13 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_strdup_ms(const char *s1)
{
	char	*str;
	size_t	i;
	size_t	lens;

	i = 0;
	lens = ft_strlen_ms(s1);
	if (!s1)
		return (0);
	if (ft_strcmp_ms(s1, "\0") == 0)
		return ("\0");
	str = (char *)malloc(sizeof(char) * lens + 1);
	if (str == NULL)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
