#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	k;
	char	*str;

	k = 0;
	if (!s || !f)
		return (NULL);
	i = ft_strlen(s);
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	while (s[k])
	{
		str[k] = (*f)((unsigned int)k, s[k]);
		k++;
	}
	str[k] = '\0';
	return (str);
}
