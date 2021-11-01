#include "../mslib.h"

char	*ft_strnstrMS(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlenMS(str2) == 0)
		return ((char *)str1);
	while (i + j < len && str1[i])
	{
		if (str1[i + j] == str2[j])
		{
			j++;
			if (str2[j] == '\0')
				return ((char *)str1 + i);
		}
		else
		{
			i++;
			j = 0;
		}
	}
	return (0);
}
