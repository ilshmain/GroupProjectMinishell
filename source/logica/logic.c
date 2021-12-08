/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:13:56 by fmint             #+#    #+#             */
/*   Updated: 2021/12/06 14:13:59 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// builtFunc********************************
int	built_func(t_gnrl *zik, t_list *ptr)
{
	int		i;

	i = 0;
	if (ft_strcmp(zik->cmd->command_array[0], "cd") == 0)
		i = cd_built(ptr, zik, -1);
	if (ft_strcmp(zik->cmd->command_array[0], "pwd") == 0)
		i = pwd_built();
	if (ft_strcmp(zik->cmd->command_array[0], "echo") == 0)
		i = echo_built(zik, 0, 1);
	if (ft_strcmp(zik->cmd->command_array[0], "env") == 0)
		i = print_env_built(ptr);
	if (ft_strcmp(zik->cmd->command_array[0], "export") == 0)
		i = export_built(ptr, zik);
	if (ft_strcmp(zik->cmd->command_array[0], "unset") == 0)
		i = unset_built(ptr, zik, 0, 0);
	if (ft_strcmp(zik->cmd->command_array[0], "exit") == 0)
		i = exit_built(zik->cmd->command_array, &zik->ptr);
	clear_envp(zik->env);
	zik->env = env(ptr);
	return (i);
}

void	free_command_array(char **envp, int ident)
{
	int	i;

	i = 0;
	if (envp)
	{
		if ((ft_strcmp(envp[0], "echo") != 0) || ident == 1)
		{
			while (envp[i] && envp[i][0] != '\0')
			{
				free(envp[i]);
				i++;
			}
		}
		else if (envp[1] && ft_strcmp(envp[1], "-n") == 0)
			while (i < 3 && envp[i])
				free(envp[i++]);
		else if (envp[1] && ft_strcmp(envp[1], "") != 0)
			while (i < 2)
				free(envp[i++]);
		else
			free(envp[0]);
		free(envp);
		envp = NULL;
	}
}

void	ft_lstdelone(t_cmnd *lst)
{
	if (lst)
	{
		free_command_array(lst->command_array, 0);
		free_command_array(lst->heredoc, 1);
	}
	free(lst);
	lst = NULL;
}

void	lstclear(t_cmnd **lst)
{
	t_cmnd	*new;

	if (!lst)
		return ;
	while (*lst)
	{
		new = (*lst)->next_list;
		ft_lstdelone(*lst);
		(*lst) = new;
	}
}

// *****************************************

int	logica(t_gnrl **zik)
{
	t_cmnd	*cmd;

	cmd = (*zik)->cmd;
	work_with_pipe(zik);
	lstclear(&cmd);
	return (1);
}
