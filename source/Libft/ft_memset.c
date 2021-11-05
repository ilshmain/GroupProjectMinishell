#include "libft.h"

void 	*ft_memset (void *b, int c, size_t len)
{
	size_t	i;
	char	*dst;

	i = 0;
	dst = b;
	while (i < len)
	{
		dst[i] = (char )c;
		i++;
	}
	return (dst);
}
