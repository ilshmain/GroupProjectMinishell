#include "mslib.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;
	size_t	lens;

	i = 0;
	lens = ft_strlen(s1);
	if (!s1)
		return (0);
	if (ft_strcmp(s1, "\0") == 0)
		return ("\0");
	str = (char *)malloc(sizeof(char) * lens + 1);
	if (str == NULL)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
