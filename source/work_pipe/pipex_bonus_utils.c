/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:21:05 by fmint             #+#    #+#             */
/*   Updated: 2021/11/29 12:21:07 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	len_lst(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**env(t_list *lst)
{
	char	**new_env;
	int		len;
	int		i;

	i = 0;
	len = len_lst(lst);
	new_env = malloc(sizeof(char *) * (len + 1));
	while (lst)
	{
		new_env[i] = ft_strdup(lst->str);
		lst = lst->next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	pid_children(t_gnrl **zik, t_cmnd *start)
{
	while (start->next_list)
	{
		close(start->fd[0]);
		close(start->fd[1]);
		start = start->next_list;
	}
	if ((built_func((*zik), (*zik)->ptr) == 1) && ((*zik)->cmd->fork == 1))
		exit (exit_code);
	pars_envp((*zik)->env, (*zik)->cmd->command_array, 0, 0);
	return (1);
}
