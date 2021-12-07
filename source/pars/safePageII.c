/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safePageII.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:25:21 by hportife          #+#    #+#             */
/*   Updated: 2021/12/07 17:25:23 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**fake_split(char *str, char sym)
{
	char	**tmp;
	int		i;
	int		j;
	int		qt;

	if (!str)
		return (0);
	i = -1;
	j = 0;
	qt = 0;
	tmp = (char **)malloc(sizeof (char *) * get_qt_str(str, ' ') + 1);
	while (str[++i])
	{
		if (str[i] == sym && (str[i + 1] != '\0' || qt == 0))
		{
			tmp[qt++] = ft_substr(str, j, i - j);
			j = i + 1;
			while (str[i] && str[i++] == sym)
				;
		}
	}
	if (str[j] != '\0')
		tmp[qt++] = ft_substr(str, j, i - j);
	tmp[qt] = NULL;
	return (tmp);
}

int	no_one_symbol_in_str(char *str, char sym)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] != sym)
			return (1);
	return (0);
}

int	get_qt_str(char *str, char sym)
{
	int	i;
	int	qt;

	if (!str || str[0] == '\0')
		return (0);
	qt = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == sym)
		{
			while (str[i])
			{
				i++;
				if (str[i] != sym && str[i] != '\0')
				{
					qt++;
					break ;
				}
			}
		}
		i++;
	}
	return (qt);
}

void	bin_dir_check(char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (cmd[0] && cmd[0][0] == '/' && cmd[0][1] == 'b'
		&& cmd[0][2] == 'i' && cmd[0][3] == 'n'
		&& cmd[0][4] == '/')
	{
		i = 5;
		while (cmd[0][i] && cmd[0][i] != ' ')
			i++;
		tmp = ft_substr_ms(cmd[0], 0, i);
		if (!access(tmp, F_OK | X_OK))
		{
			free(cmd[0]);
			cmd[0] = pre_use_substr(tmp, 5, ft_strlen_ms(tmp) - 5);
		}
	}
}

char	*space_cut_for_ffnc(char **line, int *i)
{
	char	*tmp;

	tmp = pre_use_str_join(ft_substr(line[0], 0, *i), &line[0][*i + 1]);
	free(*line);
	return (tmp);
}
