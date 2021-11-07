#include "../../../include/minishell.h"

size_t	ft_strlcatMS(char *dst, const char *src, size_t size)
{
	size_t		dsts;
	size_t		srcs;
	size_t		i;
	size_t		j;

	dsts = ft_strlenMS(dst);
	srcs = ft_strlenMS(src);
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
