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
	if (ft_strcmp(zik->cmd->command_array[0], "bash") == 0)
		i = levelUpBash(ptr);
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

//int main(int ac, char **av, char **env)
//{
//	t_gnrl *zik = malloc(sizeof(zik) * 20);// выделяем память под структуры
//	initialEnv(env, &zik->ptr, 0);
//	zik->cmd = malloc(sizeof(t_cmnd *) * 20);// выделяем память под структуры
//	zik->env = env; // записываем енв
//
//	// первый лист команды
//	zik->cmd->command_array = ft_split("pwd", ' ');
////	zik->cmd->fd_write = open(av[2], O_WRONLY | O_CREAT | O_APPEND, 0777);
//	zik->cmd->nextList = NULL;
//
////	// второй лист команды
////	zik->cmd->nextList = malloc(sizeof(t_cmnd) * 20);
////	zik->cmd->nextList->command_array = ft_split("cat -e", ' ');
//////	zik->cmd->nextList->fd_open = open(av[1], O_RDONLY);
//////	zik->cmd->nextList->fd_reWrite = open(av[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
////	zik->cmd->nextList->nextList = NULL;
////
////	// третий лист команды
////	zik->cmd->nextList->nextList = malloc(sizeof(t_cmnd) * 10);
////////	zik->cmd->nextList->nextList->fd_open = open(av[2], O_RDONLY);
////	zik->cmd->nextList->nextList->command_array = ft_split("cat -e", ' ');
////	zik->cmd->nextList->nextList->nextList = NULL ;
////////
////	// четвертый лист команды
////	zik->cmd->nextList->nextList->nextList = malloc(sizeof(t_cmnd) * 1);
////	zik->cmd->nextList->nextList->nextList->command_array = ft_split("cat -e", ' ');
////	zik->cmd->nextList->nextList->nextList->nextList = NULL;
//	logica(&zik);
//}