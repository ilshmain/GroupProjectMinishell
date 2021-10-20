#include "mslib.h"

void	error_call(char *message)
{
	ft_putstr_fdMS(message, 1);
	exit(0);
}
