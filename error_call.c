#include "mslib.h"

void	error_call(char *message)
{
	ft_putstr_fd(message, 1);
	exit(0);
}
