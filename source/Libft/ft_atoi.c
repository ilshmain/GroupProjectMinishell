#include "libft.h"

int	ft_atoi(const char *str)
{
	long	nbr;
	int		k;
	int		a;

	nbr = 0;
	k = 0;
	a = 1;
	while (str[k] == 32 || (str[k] > 8 && str[k] < 14))
		k++;
	if (str[k] == '+' || str[k] == '-')
	{
		if (str[k] == '-')
			a = -a;
		k++;
	}
	while (str[k] > 47 && str[k] < 58)
	{
		nbr = nbr * 10 + (str[k] - '0');
		if (nbr > 2147483647 && a == 1)
			return (-1);
		if (nbr > 2147483648 && a == -1)
			return (0);
		k++;
	}
	return (a * nbr);
}
