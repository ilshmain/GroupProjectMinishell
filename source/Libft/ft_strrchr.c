#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	k;
	int	a;

	k = 0;
	a = 0;
	while (s[a])
		a++;
	while (k < a + 1)
	{
		if (s[k] == (char)c)
		{
			while (s[k] != s[a])
				a--;
			return ((char *)s + a);
		}
		k++;
	}
	return (0);
}
