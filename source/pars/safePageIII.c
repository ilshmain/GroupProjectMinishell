/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safePageIII.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:25:28 by hportife          #+#    #+#             */
/*   Updated: 2021/12/07 17:25:30 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_tilda(char **line, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = getenv("HOME");
	tmp2 = ft_substr_ms(line[0], 0, *i + 1);
	tmp2 = pre_use_str_join(tmp2, tmp);
	tmp = ft_substr_ms(line[0], (*i) + 1, ft_strlen(line[0]) - *i + 1);
	tmp2 = pre_use_str_join(tmp2, tmp);
	free(tmp);
	free(*line);
	return (tmp2);
}

void	clear_hrd(t_list **strct)
{
	t_list	*tmp;

	tmp = (*strct);
	while (tmp->next != NULL)
	{
		free(tmp->str);
		tmp->str = NULL;
		tmp = tmp->next;
		(*strct)->next = NULL;
		free((*strct));
		(*strct) = tmp;
	}
	free(tmp->str);
	(*strct)->next = NULL;
	tmp = NULL;
	free((*strct));
	*strct = NULL;
	strct = NULL;
}

char	**clear_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (NULL);
}

int	fd_closer(int fd)
{
	if (fd != -2)
	{
		close(fd);
		fd = -2;
	}
	return (fd);
}
