/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:58:42 by fmint             #+#    #+#             */
/*   Updated: 2021/11/27 19:58:46 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//size_t	ft_strlen(const char *s)
//{
//	size_t	i;
//
//	i = 0;
//	while (s[i])
//		i++;
//	return (i);
//}
//
//char	*ft_strchr(const char *s, int c)
//{
//	size_t	k;
//	size_t	i;
//
//	k = 0;
//	i = ft_strlen(s);
//	while (k < i + 1)
//	{
//		if (s[k] == (char)c)
//			return ((char *)s + k);
//		k++;
//	}
//	return (0);
//}
//
//char	*ft_strdup(const char *s1)
//{
//	int		k;
//	char	*buf;
//
//	k = 0;
//	while (s1[k])
//		k++;
//	buf = (char *)malloc(k + 1);
//	if (buf == NULL)
//		return (NULL);
//	k = 0;
//	while (s1[k])
//	{
//		buf[k] = s1[k];
//		k++;
//	}
//	buf[k] = '\0';
//	return (buf);
//}
//
//char	*ft_strjoin(char const *s1, char const *s2)
//{
//	size_t	k;
//	size_t	p;
//	char	*buf;
//
//	if (!s1 || !s2)
//		return (0);
//	k = -1;
//	p = 0;
//	buf = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
//	if (!buf)
//		return (NULL);
//	if (s1 && !s2)
//		return (ft_strdup(s1));
//	if (!s1 && s2)
//		return (ft_strdup(s2));
//	while (s1[++k])
//		buf[k] = s1[k];
//	while (s2[p])
//		buf[k++] = s2[p++];
//	buf[k] = 0;
//	free((void *)s1);
//	return (buf);
//}

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
