#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		k;
	char	*buf;

	k = 0;
	while (s1[k])
		k++;
	buf = (char *)malloc(k + 1);
	if (buf == NULL)
		return (NULL);
	k = 0;
	while (s1[k])
	{
		buf[k] = s1[k];
		k++;
	}
	buf[k] = '\0';
	return (buf);
}
