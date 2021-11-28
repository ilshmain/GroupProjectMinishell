#include "../../include/minishell.h"

char *fnc_redir(char **line, int *i, t_gnrl **gen, int ident)
{
	int		nameLen;
	char	*nameFile;
	t_cmnd	*tmpCmd;

	tmpCmd = (*gen)->cmd;
	while (tmpCmd->next_list != NULL)
		tmpCmd = tmpCmd->next_list;
	nameFile = nameForRedir(line, &nameLen, i, gen);
	while (line[0][nameLen] && line[0][nameLen] == ' ') // пропускаем лишние пробелы
		nameLen++;
	if (ident == 1)
		fncRedirWrite(&tmpCmd, nameFile);
	else if (ident == 2)
		fncRedirReWrite(&tmpCmd, nameFile);
	else if (ident == 3)
		fncRedirHeredoc(&tmpCmd, nameFile);
	else if (ident == 4)
		fncRedirOpen(&tmpCmd, nameFile);
	free (nameFile);
	line[0] = strCutStr(line[0], *i, nameLen);
	return (line[0]);
}

void	fncRedirOpen(t_cmnd **cmd, char *nameFile) //доработать
{
	int	fd;

	if ((*cmd)->fd_open)
	{
		close((*cmd)->fd_open);
		(*cmd)->fd_open = 0;
	}//если дескриптора не было, если был, то надо закрыть
	fd = open(nameFile, O_RDONLY); // открываем на чтение
	if (fd == -1)
	{
		(*cmd)->err = 1;
		printf("%s: file does not exist or access is denied\n", nameFile);
		return ;
	}
	(*cmd)->fd_open = fd; // записываем дескриптор
}

void	fncRedirWrite(t_cmnd **cmd, char *nameFile)
{
	int fd;

	if ((*cmd)->fd_write > 0)
	{
		close((*cmd)->fd_write);
		(*cmd)->fd_write = 0;
	}
	if ((*cmd)->fd_re_write > 0)
	{
		close((*cmd)->fd_re_write);
		(*cmd)->fd_re_write = 0;
	}//если дескриптора не было, если был, то надо закрыть
	fd = open(nameFile, O_WRONLY | O_CREAT | O_APPEND, 0777); // открываем на дозапись
	if (fd == -1)
	{
		(*cmd)->err = 1;
		printf("%s: file does not exist or access is denied\n", nameFile);
		return ;
	}
	(*cmd)->fd_write = fd; // записываем дескриптор
}

void	fncRedirReWrite(t_cmnd **cmd, char *nameFile)
{
	int 	fd;

	if ((*cmd)->fd_write > 0)
	{
		close((*cmd)->fd_write);
		(*cmd)->fd_write = 0;
	}
	if ((*cmd)->fd_re_write > 0)
	{
		close((*cmd)->fd_re_write);
		(*cmd)->fd_re_write = 0;
	}//если дескриптора не было, если был, то надо закрыть
	fd = open(nameFile, O_RDWR | O_CREAT | O_TRUNC, 0777); // открываем на перезапись
	if (fd == -1)
	{
		(*cmd)->err = 1;//ОШИППППКИ)
		printf("%s: Permission denied\n", nameFile);
		return ;
	}
	(*cmd)->fd_re_write = fd; // записываем дескриптор
}

void	fncRedirHeredoc(t_cmnd **cmd, char *hereDoc)
{
	int 	i;
	char	**tmp;

	i = 0;
	if ((*cmd)->fd_open != 0)
	{
		close((*cmd)->fd_open);
		(*cmd)->fd_open = -2;
	}
	if ((*cmd)->heredoc)
		tmp = malloc(sizeof (char **) * (dual_array_len((*cmd)->heredoc) + ft_strlenMS(hereDoc)));
	else
		tmp = malloc(sizeof (char **) * (ft_strlenMS(hereDoc)));
	while ((*cmd)->heredoc && (*cmd)->heredoc[i] != NULL)
	{
		tmp[i] = ft_strdup((*cmd)->heredoc[i]);
		free ((*cmd)->heredoc[i]);
		i++;
	}
	tmp[i] = ft_strdup(hereDoc);
	free ((*cmd)->heredoc);
	(*cmd)->heredoc = tmp;
}