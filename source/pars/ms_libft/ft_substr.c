#include "../../../include/minishell.h"

char	*ft_substrMS(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlenMS(s))
		return (ft_strdupMS(""));
	if ((start + len) < ft_strlenMS(s))
		res = (char *)malloc(sizeof(*s) * len + 1);
	else
		res = (char *)malloc(sizeof(*s) * ft_strlenMS(s) - start + 1);
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
