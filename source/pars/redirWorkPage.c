/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirWorkPage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hportife <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:59:16 by hportife          #+#    #+#             */
/*   Updated: 2021/11/29 13:59:18 by hportife         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*fnc_redir(char **line, int *i, t_gnrl **gen, int ident)
{
	int		name_len;
	char	*name_file;
	t_cmnd	*tmp_cmd;

	tmp_cmd = (*gen)->cmd;
	while (tmp_cmd->next_list != NULL)
		tmp_cmd = tmp_cmd->next_list;
	name_file = name_for_redir(line, &name_len, i, gen);
	while (line[0][name_len] && line[0][name_len] == ' ')
		name_len++;
	if (ident == 1)
		fnc_redir_write(&tmp_cmd, name_file);
	else if (ident == 2)
		fnc_redir_re_write(&tmp_cmd, name_file);
	else if (ident == 3)
		tmp_cmd->heredoc = fnc_redir_heredoc(&tmp_cmd, name_file);
	else if (ident == 4)
		fnc_redir_open(&tmp_cmd, name_file);
	for (int j = 0; tmp_cmd->heredoc[j]; ++j) {
		printf("|%s|\n", tmp_cmd->heredoc[j]);
	}
	free (name_file);
	line[0] = str_cut_str(line[0], *i, name_len);
	return (line[0]);
}

void	fnc_redir_open(t_cmnd **cmd, char *name_file)
{
	int	fd;

	if ((*cmd)->fd_open)
	{
		close((*cmd)->fd_open);
		(*cmd)->fd_open = 0;
	}
	fd = open(name_file, O_RDONLY);
	if (fd == -1)
	{
		(*cmd)->err = 1;
		perror(name_file);
		return ;
	}
	(*cmd)->fd_open = fd;
}

void	fnc_redir_write(t_cmnd **cmd, char *name_file)
{
	int	fd;

	if ((*cmd)->fd_write > 0)
	{
		close((*cmd)->fd_write);
		(*cmd)->fd_write = 0;
	}
	if ((*cmd)->fd_re_write > 0)
	{
		close((*cmd)->fd_re_write);
		(*cmd)->fd_re_write = 0;
	}
	fd = open(name_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		(*cmd)->err = 1;
		perror(name_file);
		return ;
	}
	(*cmd)->fd_write = fd;
}

void	fnc_redir_re_write(t_cmnd **cmd, char *nameFile)
{
	int	fd;

	if ((*cmd)->fd_write > 0)
	{
		close((*cmd)->fd_write);
		(*cmd)->fd_write = 0;
	}
	if ((*cmd)->fd_re_write > 0)
	{
		close((*cmd)->fd_re_write);
		(*cmd)->fd_re_write = 0;
	}
	fd = open(nameFile, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		(*cmd)->err = 1;
		perror(nameFile);
		return ;
	}
	(*cmd)->fd_re_write = fd;
}

char	**fnc_redir_heredoc(t_cmnd **cmd, char *here_doc)
{
	int		i;
	char	**tmp;

	i = 0;
	if ((*cmd)->fd_open != -2)
	{
		close((*cmd)->fd_open);
		(*cmd)->fd_open = -2;
	}
	tmp = (char **)malloc(sizeof (char *)
			* (dual_array_len((*cmd)->heredoc) + 1));
	while ((*cmd)->heredoc != NULL && (*cmd)->heredoc[i] != NULL)
	{
		tmp[i] = ft_strdup_ms((*cmd)->heredoc[i]);
		i++;
	}
	tmp[i] = ft_strdup_ms(here_doc);
	tmp[i + 1] = NULL;
	int j = 0;
	while (j < dual_array_len((*cmd)->heredoc))
	{
		free((*cmd)->heredoc[j]);
		j++;
	}
	if ((*cmd)->heredoc)
		free((*cmd)->heredoc);
	return (tmp);
}
