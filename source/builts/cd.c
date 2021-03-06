/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:31:29 by fmint             #+#    #+#             */
/*   Updated: 2021/11/25 18:31:32 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// cd BUILT*****************************
char	*use_way(t_list *ptr, char *comand)
{
	int		i;
	char	*new_way;

	new_way = NULL;
	i = (int)ft_strlen(comand);
	while (ptr)
	{
		if ((ft_strncmp(ptr->str, comand, i) == 0))
		{
			new_way = change_ft_strrchr(ptr->str, '=');
			break ;
		}
		ptr = ptr->next;
	}
	return (new_way);
}

void	change_str_value(t_list *ptr, char *wayAfterChange, char *wayToChange)
{
	while (ptr)
	{
		if (ft_strncmp(ptr->str, "PWD", 3) == 0)
		{
			free(ptr->str);
			ptr->str = ft_strjoin("PWD=", wayAfterChange);
		}
		if (ft_strncmp(ptr->str, "OLDPWD=", 7) == 0)
		{
			free(ptr->str);
			ptr->str = ft_strjoin("OLDPWD=", wayToChange);
		}
		ptr = ptr->next;
	}
	free(wayToChange);
	free(wayAfterChange);
}

void	oldpwd_way(t_list *ptr)
{
	char	*str;

	str = ft_strdup(use_way(ptr, "OLDPWD="));
	g_exit_code = chdir(str);
	if (g_exit_code == -1)
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell$ cd: OLDPWD not set\n", STDERR_FILENO);
	}
	ft_putendl_fd(str, STDOUT_FILENO);
	free(str);
}

int	other_way(t_gnrl *zik)
{
	g_exit_code = 1;
	ft_putstr_fd("minishell$ cd: ", STDERR_FILENO);
	ft_putstr_fd(zik->cmd->command_array[1], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (1);
}

int	cd_built(t_list *ptr, t_gnrl *zik, int i)
{
	char	*way_to_change;
	char	*way_after_change;

	while (zik->cmd->command_array[++i])
		;
	way_to_change = getcwd(NULL, 1024);
	if (way_to_change == NULL)
	{
		free(way_to_change);
		way_to_change = use_way(ptr, "PWD=");
	}
	if (i == 1)
		g_exit_code = chdir(use_way(ptr, "HOME="));
	else if (ft_strcmp(zik->cmd->command_array[1], "-") == 0)
		oldpwd_way(ptr);
	else
		g_exit_code = chdir(zik->cmd->command_array[1]);
	if (g_exit_code == -1)
		return (other_way(zik));
	else
		g_exit_code = 0;
	way_after_change = getcwd(NULL, 1024);
	change_str_value(ptr, way_after_change, way_to_change);
	return (1);
}
//**************************************
