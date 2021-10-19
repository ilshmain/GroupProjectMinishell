#include "mslib.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if ((start + len) < ft_strlen(s))
		res = (char *)malloc(sizeof(*s) * len + 1);
	else
		res = (char *)malloc(sizeof(*s) * ft_strlen(s) - start + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}
