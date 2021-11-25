#include "../../include/minishell.h"

// builtFunc********************************
int	builtFunc(t_gnrl *zik, t_list *ptr)
{
	char 	**per;
	int 	i;

	i = 0;
	if (ft_strcmp(zik->cmd->command_array[0], "cd") == 0)
		i = cdBuilt(ptr, zik);
	if (ft_strcmp(zik->cmd->command_array[0], "pwd") == 0)
		i = pwdBuilt();
	if (ft_strcmp(zik->cmd->command_array[0], "echo") == 0)
		i = echoBuilt(zik);
	if (ft_strcmp(zik->cmd->command_array[0], "env") == 0)
		i = printEnvBuilt(ptr);
	if (ft_strcmp(zik->cmd->command_array[0], "export") == 0)
		i = exportBuilt(ptr, zik);
	if (ft_strcmp(zik->cmd->command_array[0], "unset") == 0)
		i = unsetBuilt(ptr, zik);
	if (ft_strcmp(zik->cmd->command_array[0], "exit") == 0)
		i = exit_built(zik->cmd->command_array, &zik->ptr);
	per = env(zik->ptr);
	zik->env = per;
	free(per);
	return (i);
}

void	free_command_array(char **envp)
{
	int i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			free(envp[i]);
			i++;
		}
	}
}

void	ft_lstdelone(t_cmnd *lst)
{
	if (lst)
	{
		free_command_array(lst->command_array);
		free_command_array(lst->heredoc);
		free(lst->errContext);
	}
	free(lst);
	lst = NULL;
}

void	lstclear(t_cmnd **lst)
{
	t_cmnd 	*new;

	if (!lst)
		return ;
	while (*lst)
	{
		new = (*lst)->nextList;
		ft_lstdelone(*lst);
		(*lst) = new;
	}
}

// *****************************************

int logica(t_gnrl **zik)
{
	work_with_pipe(zik);
//	lstclear(&(*zik)->cmd);
	return (1);
}