#include "../../include/minishell.h"

int	pwd_built(void)
{
	char	pwd[1024];

	exit_code = 0;
	getcwd(pwd, 1024);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (1);
}
