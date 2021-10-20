#include "../include/minishell.h"

void	pwdBuilt()
{
	char	pwd[1000];

	getcwd(pwd, 1000);
	printf("%s\n", pwd);
}