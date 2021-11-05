#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			k;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	k = 0;
	while (k < n)
	{
		if ((p1[k]-p2[k]) == 0)
			k++;
		else
			return (p1[k] - p2[k]);
	}
	return (0);
}
