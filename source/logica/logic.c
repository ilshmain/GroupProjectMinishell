#include "../../include/minishell.h"

//// builtFunc********************************
//void	builtFunc(t_gnrl *zik, t_list *ptr)
//{
//	if (ft_strcmp(zik->cmd->command_array[0], "cd") == 0)
//		cdBuilt(ptr, zik);
//	if (ft_strcmp(zik->cmd->command_array[0], "pwd") == 0)
//		pwdBuilt();
//	if (ft_strcmp(zik->cmd->command_array[0], "echo") == 0)
//		echoBuilt(zik);
//	if (ft_strcmp(zik->cmd->command_array[0], "env") == 0)
//		printEnvBuilt(ptr);
//	if (ft_strcmp(zik->cmd->command_array[0], "export") == 0)
//		exportBuilt(ptr, zik);
//	if (ft_strcmp(zik->cmd->command_array[0], "bash") == 0)
//		levelUpBash(ptr);
//	if (ft_strcmp(zik->cmd->command_array[0], "unset") == 0)
//		unsetBuilt(ptr, zik);
////	printEnvBuilt(ptr);
//}

// *****************************************

int logica(t_gnrl **zik)
{
	work_with_pipe(zik);
	return (1);
}

int main(int ac, char **av, char **env)
{
	t_gnrl *zik = malloc(sizeof(zik) * 10);// выделяем память под структуры
	zik->ptr = malloc(sizeof(t_list *) * 10);// выделяем память под структуры
	zik->cmd = malloc(sizeof(t_cmnd *) * 10);// выделяем память под структуры
	zik->env = env; // записываем енв
	zik->cmd->heredoc = NULL;

	// первый лист команды
	zik->cmd->command_array = ft_split("ls -la", ' ');

	zik->cmd->fd_write = 0;
	zik->cmd->fd_reWrite = 0;
	zik->cmd->fd_open = 0;

	// второй лист команды
	zik->cmd->nextList = malloc(sizeof(t_cmnd) * 10);
	zik->cmd->nextList->command_array = ft_split("cat -e", ' ');
//	zik->cmd->nextList->nextList = NULL;

	// третий лист команды
	zik->cmd->nextList->nextList = malloc(sizeof(t_cmnd) * 10);
	zik->cmd->nextList->nextList->command_array = ft_split("cat -e", ' ');
//
	// четвертый лист команды
	zik->cmd->nextList->nextList->nextList = malloc(sizeof(t_cmnd) * 1);
	zik->cmd->nextList->nextList->nextList->command_array = ft_split("cat -e", ' ');
	zik->cmd->nextList->nextList->nextList->nextList = NULL;
	logica(&zik);
}