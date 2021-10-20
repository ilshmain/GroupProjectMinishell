#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	*s1;
	unsigned char	sym;
	size_t			k;

	s = dst;
	s1 = (unsigned char *)src;
	sym = c;
	k = 0;
	while (k < n)
	{
		s[k] = s1[k];
		if (s1[k] == sym)
		{
			return ((void *)(s + k +1));
		}
		k++;
	}
	return (NULL);
}
