#include "../../include/minishell.h"

// builtFunc********************************
int	builtFunc(t_gnrl *zik, t_list *ptr)
{
	int i;

	i = 0;
	if (ft_strcmp(zik->cmd->command_array[0], "cd") == 0)
		i = cdBuilt(ptr, zik);
	if (ft_strcmp(zik->cmd->command_array[0], "pwd") == 0)
		i = pwdBuilt(zik->env);
	if (ft_strcmp(zik->cmd->command_array[0], "echo") == 0)
		i = echoBuilt(zik);
	if (ft_strcmp(zik->cmd->command_array[0], "env") == 0)
		i = printEnvBuilt(ptr);
	if (ft_strcmp(zik->cmd->command_array[0], "export") == 0)
		i = exportBuilt(ptr, zik);
	if (ft_strcmp(zik->cmd->command_array[0], "unset") == 0)
		i = unsetBuilt(ptr, zik);
	return (i);
//	printEnvBuilt(ptr);
}

// *****************************************

int logica(t_gnrl **zik)
{
	work_with_pipe(zik);
	return (1);
}