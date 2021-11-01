#include "../mslib.h"

size_t	ft_strlenMS(const char *str)
{
	int	k;

	k = 0;
	if (str == NULL)
		return (0);
	while (str[k])
		k++;
	return (k);
}
