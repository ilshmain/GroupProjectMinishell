#include "../../include/minishell.h"

int	size_two_poineter_mas(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	echo_built(t_gnrl *zik)
{
	int	i;

	i = size_two_poineter_mas(zik->cmd->command_array);
	if (i == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (ft_strcmp(zik->cmd->command_array[1], "-n") == 0)
	{
		if (i == 2)
			ft_putstr_fd("", STDOUT_FILENO);
		else
			ft_putstr_fd(zik->cmd->command_array[2], STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(zik->cmd->command_array[1], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	exit_code = 0;
	return (1);
}
