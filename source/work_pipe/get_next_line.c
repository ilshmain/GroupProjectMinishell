/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:58:15 by fmint             #+#    #+#             */
/*   Updated: 2021/11/27 19:58:18 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*checkostatok(char **line, char **ostatok)
{
	char	*reminder;

	reminder = NULL;
	if (*ostatok)
	{
		reminder = ft_strchr(*ostatok, '\n');
		if (reminder)
		{
			*reminder = '\0';
			*line = ft_strdup(*ostatok);
			ft_strcpy(*ostatok, ++reminder);
		}
		else
		{
			*line = ft_strdup(*ostatok);
			free(*ostatok);
			*ostatok = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (reminder);
}

int	proverka(int fd, char **line, char *buf)
{
	int			i;
	char		*simv_kontsa_stroki;
	static char	*ostatok;

	i = 1;
	simv_kontsa_stroki = checkostatok(line, &ostatok);
	while (!simv_kontsa_stroki && i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		buf[i] = '\0';
		simv_kontsa_stroki = ft_strchr(buf, '\n');
		if (simv_kontsa_stroki)
		{
			*simv_kontsa_stroki = '\0';
			ostatok = ft_strdup(++simv_kontsa_stroki);
		}
		*line = ft_strjoin(*line, buf);
	}
	free(buf);
	return (i && ostatok);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;

	if (read(fd, NULL, 0) < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	return (proverka(fd, line, buf));
}
