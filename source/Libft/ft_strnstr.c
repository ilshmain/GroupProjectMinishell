#include "libft.h"

char	*ft_strnstr (const char *dst, const char *src, size_t len)
{
	size_t	k;
	size_t	p;

	k = 0;
	if (src[0] == '\0')
		return ((char *)dst);
	while (k < len && dst[k])
	{
		p = 0;
		while (dst[k + p] == src[p] && (p + k) < len)
		{
			p++;
			if (src[p] == '\0')
				return ((char *)(dst + k));
		}
		k++;
	}
	return (0);
}
