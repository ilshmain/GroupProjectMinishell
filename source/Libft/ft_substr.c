#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	k;
	char	*buf;

	k = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s) < len + start)
		buf = (char *)malloc(ft_strlen(s) - start + 1);
	else
		buf = (char *)malloc(len + 1);
	if (buf == NULL)
		return (NULL);
	while ((k < len) && (s[start + k]))
	{
		buf[k] = s[start + k];
		k++;
	}
	buf[k] = '\0';
	return (buf);
}
