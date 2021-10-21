#include "include/minishell.h"

// builtFunc********************************
void	builtFunc(t_gnrl *zik, t_list *ptr)
{
	if (ft_strcmp(zik->cmd->command_array[0], "cd") == 0)
		cdBuilt(ptr, zik);
	if (ft_strcmp(zik->cmd->command_array[0], "pwd") == 0)
		pwdBuilt();
	if (ft_strcmp(zik->cmd->command_array[0], "echo") == 0)
		echoBuilt(zik);
	if (ft_strcmp(zik->cmd->command_array[0], "env") == 0)
		printEnvBuilt(ptr);
	if (ft_strcmp(zik->cmd->command_array[0], "export") == 0)
		exportBuilt(ptr, zik);
	if (ft_strcmp(zik->cmd->command_array[0], "bash") == 0)
		levelUpBash(ptr);
	if (ft_strcmp(zik->cmd->command_array[0], "unset") == 0)
		unsetBuilt(ptr, zik);
//	printEnvBuilt(ptr);
}

// *****************************************

int logica(t_gnrl **zik)
{
	while ((*zik)->cmd->nextList)
	{
		if ((*zik)->cmd->flg_pipe == 1)
			builtFunc((*zik), (*zik)->ptr);
		(*zik)->cmd = (*zik)->cmd->nextList;
	}
	builtFunc((*zik), (*zik)->ptr);
	return (1);
}