/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servFnc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:59:36 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 13:59:38 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_putstr_fd_ms(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

t_cmnd	*ft_lstnew_ms(void)
{
	t_cmnd	*tmp;

	tmp = malloc(sizeof (t_cmnd) * 1);
	tmp->command_array = NULL;
	tmp->flg_butil = 0;
	tmp->flg_pipe = 0;
	tmp->fd_re_write = -2;
	tmp->fd_write = -2;
	tmp->fd_open = -2;
	tmp->heredoc = NULL;
	tmp->err = 0;
	tmp->next_list = NULL;
	return (tmp);
}

char	*str_cut_str(char *inStr, int startOfCut, int endOfCut)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_substr_ms(inStr, 0, startOfCut);
	tmp1 = ft_substr_ms(inStr, endOfCut, ft_strlen(inStr));
	free (inStr);
	inStr = pre_use_str_join(tmp, tmp1);
	if (tmp1 && ft_strcmp_ms(tmp1, "") != 0)
		free(tmp1);
	return (inStr);
}

void	butils_prov(t_cmnd **command)
{
	if (ft_strcmp((*command)->command_array[0], "echo") == 0)
		(*command)->flg_butil = 1;
	else if (ft_strcmp((*command)->command_array[0], "cd") == 0)
		(*command)->flg_butil = 1;
	else if (ft_strcmp((*command)->command_array[0], "pwd") == 0)
		(*command)->flg_butil = 1;
	else if (ft_strcmp((*command)->command_array[0], "export") == 0)
		(*command)->flg_butil = 1;
	else if (ft_strcmp((*command)->command_array[0], "unset") == 0)
		(*command)->flg_butil = 1;
	else if (ft_strcmp((*command)->command_array[0], "env") == 0)
		(*command)->flg_butil = 1;
	else if (ft_strcmp((*command)->command_array[0], "exit") == 0)
		(*command)->flg_butil = 1;
}
