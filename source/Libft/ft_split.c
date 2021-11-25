/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:52:46 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:52:48 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_schet_kol_slov(char const *s, char c)
{
	unsigned int	i;
	unsigned int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			k++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (k);
}

static unsigned int	memory_slov(char const *s, unsigned int *ukaz, char c)
{
	unsigned int	k;

	k = 0;
	while (s[*ukaz] && s[*ukaz] == c)
		(*ukaz)++;
	while (s[*ukaz] && s[*ukaz] != c)
	{
		(*ukaz)++;
		k++;
	}
	return (k);
}

static char	**memory_clear(char **s)
{
	unsigned int	k;

	k = 0;
	while (s[k])
	{
		free(s[k]);
		k++;
	}
	free(s);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	kolvo_slov;
	unsigned int	per;
	unsigned int	ukaz;
	unsigned int	len;
	char			**out;

	per = 0;
	ukaz = 0;
	if (!s)
		return (0);
	kolvo_slov = ft_schet_kol_slov(s, c);
	out = (char **)malloc(sizeof(char *) * (kolvo_slov + 1));
	if (!out)
		return (NULL);
	while (per < kolvo_slov)
	{
		len = memory_slov(s, &ukaz, c);
		out[per] = (char *)malloc(sizeof(char) * (len + 1));
		if (!out[per])
			return (memory_clear(out));
		ft_strlcpy(out[per], &s[ukaz - len], len + 1);
		per++;
	}
	out[per] = 0;
	return (out);
}
