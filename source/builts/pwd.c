#include "../../include/minishell.h"

int	pwdBuilt()
{
	exit_code = 0;
	char	pwd[1024];
	getcwd(pwd, 1024);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return 1;
}
