#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123) || (c == 61))
		return (1);
	return (0);
}
