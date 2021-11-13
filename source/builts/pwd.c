#include "../../include/minishell.h"

void	*ms_malloc_x(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

int	pwdBuilt(char **envp)
{
	(void)envp;
	char	*pwd;
	int		i;

	pwd = ms_malloc_x(sizeof(*pwd) * 2048);
	i = -1;
	while (++i < 2048)
		pwd[i] = 0;
	if (getcwd(pwd, 2048))
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
		return (0);
	}
	else
	{
		ft_putendl_fd("strerror(errno)", STDERR_FILENO);
		free(pwd);
		return (1);
	}
}