#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	k;

	k = 0;
	if (!src || !dst)
		return (0);
	if (dstsize > 0)
	{
		while (src[k] && k < dstsize - 1)
		{
			dst[k] = src[k];
			k++;
		}
		dst[k] = '\0';
		return (ft_strlen(src));
	}
	while (src[k])
		k++;
	return (ft_strlen(src));
}
