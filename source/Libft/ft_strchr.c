#include "libft.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	size_t	k;

	k = 0;
	while (k < ft_strlen(s) + 1)
	{
		if (s[k] == (char)c)
		{
			return ((char *)s + k);
		}
		k++;
	}
	return (0);
}
