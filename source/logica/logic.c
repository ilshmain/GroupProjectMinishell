#include "../../include/minishell.h"

// builtFunc********************************
int	built_func(t_gnrl *zik, t_list *ptr)
{
	int		i;

	i = 0;
	if (ft_strcmp(zik->cmd->command_array[0], "cd") == 0)
		i = cd_built(ptr, zik, 0);
	if (ft_strcmp(zik->cmd->command_array[0], "pwd") == 0)
		i = pwd_built();
	if (ft_strcmp(zik->cmd->command_array[0], "echo") == 0)
		i = echo_built(zik);
	if (ft_strcmp(zik->cmd->command_array[0], "env") == 0)
		i = print_env_built(ptr);
	if (ft_strcmp(zik->cmd->command_array[0], "export") == 0)
		i = export_built(ptr, zik);
	if (ft_strcmp(zik->cmd->command_array[0], "unset") == 0)
		i = unset_built(ptr, zik);
	if (ft_strcmp(zik->cmd->command_array[0], "exit") == 0)
		i = exit_built(zik->cmd->command_array, &zik->ptr);
	return (i);
}

void	free_command_array(char **envp)
{
	int i;

	i = 0;
	if (envp)
	{
		if (ft_strcmp(envp[0], "echo") != 0)
			while (envp[i] && envp[i][0] != '\0')
			{
				free(envp[i]);
				i++;
			}
		else if (envp[1] && ft_strcmp(envp[1], "-n") == 0)
			while (i < 3 && envp[i])
				free(envp[i++]);
		else if (envp[1] && ft_strcmp(envp[1], "") != 0)
			while (i < 2)
				free(envp[i++]);
		else
			free(envp[0]);
	}
		free(envp);
}

void	ft_lstdelone(t_cmnd *lst)
{
	if (lst)
	{
		free_command_array(lst->command_array);
		free_command_array(lst->heredoc);
//		if (lst->errContext)
//			free(lst->errContext);
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
	lstclear(&(*zik)->cmd);
	return (1);
}