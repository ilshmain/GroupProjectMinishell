#include "../../include/minishell.h"

int	echoBuilt(t_gnrl *zik)
{
	if (ft_strcmp(zik->cmd->command_array[1], "-") == 0)
		printf("%s\n", zik->cmd->command_array[2]);
	else if (ft_strcmp(zik->cmd->command_array[1], "-n") == 0)
		printf("%s", zik->cmd->command_array[2]);
	else
		printf("%s\n", zik->cmd->command_array[1]);
	return (1);
}