#include "mslib.h"

char *fnc_redir(char *line, int *i, t_gnrl **gen, int ident)
{
	int nameLen;
	char *nameFile;

	nameLen = *i;
	while (ft_isalnumMS(line[nameLen]) == 0) // пропускаем символы, которые не могут входить в нейминг
		nameLen++;
	line = strCutStr(line, *i, nameLen);
	nameLen = *i;
	while (line[nameLen] && line[nameLen] != ' ') // пропускаем символы, которые не могут входить в нейминг
		nameLen++;
	nameFile = ft_substr(line, *i, nameLen - *i);// берём имя
	while (line[nameLen] && line[nameLen] == ' ') // пропускаем лишние пробелы
		nameLen++;
	if (ident == 1)
		fncRedirWrite(line, gen, nameFile);
	else if (ident == 2)
		fncRedirReWrite(line, gen, nameFile);
	else if (ident == 3)
		fncRedirHeredoc(gen, nameFile);
	else if (ident == 4)
		fncRedirOpen(line, gen, nameFile);
	free (nameFile);
	line = strCutStr(line, *i, nameLen);
	return (line);
}

void	fncRedirOpen(char *line, t_gnrl **gen, char *nameFile) //доработать
{
	int	fd;

	if ((*gen)->cmd->fd_open)
	{
		close((*gen)->cmd->fd_open);
		(*gen)->cmd->fd_open = 0;
	}//если дескриптора не было, если был, то надо закрыть
	fd = open(nameFile, O_RDONLY); // открываем на чтение
	if (fd == -1)
	{
		(*gen)->errors = 1;
		return ;
	}
	(*gen)->cmd->fd_open = fd; // записываем дескриптор
}

void	fncRedirWrite(char *line, t_gnrl **gen, char *nameFile)
{
	int fd;

	if ((*gen)->cmd->fd_write)
	{
		close((*gen)->cmd->fd_write);
		(*gen)->cmd->fd_write = 0;
	}
	if ((*gen)->cmd->fd_reWrite)
	{
		close((*gen)->cmd->fd_reWrite);
		(*gen)->cmd->fd_reWrite = 0;
	}//если дескриптора не было, если был, то надо закрыть
	fd = open(nameFile, O_CREAT); // открываем на дозапись
	if (fd == -1)
	{
		(*gen)->errors = 1;
		return ;
	}
	(*gen)->cmd->fd_write = fd; // записываем дескриптор
}

void	fncRedirReWrite(char *line, t_gnrl **gen, char *nameFile)
{
	int fd;

	if ((*gen)->cmd->fd_write)
	{
		close((*gen)->cmd->fd_write);
		(*gen)->cmd->fd_write = 0;
	}
	if ((*gen)->cmd->fd_reWrite)
	{
		close((*gen)->cmd->fd_reWrite);
		(*gen)->cmd->fd_reWrite = 0;
	}//если дескриптора не было, если был, то надо закрыть
	fd = open(nameFile, O_TRUNC); // открываем на перезапись
	if (fd == -1) //если файла не существует, создаём
		fd = open(nameFile, O_CREAT);
	if (fd == -1)
	{
		(*gen)->errors = 1;//ОШИППППКИ)
		return ;
	}
	(*gen)->cmd->fd_reWrite = fd; // записываем дескриптор
}

void	fncRedirHeredoc(t_gnrl **gen, char *hereDoc)
{
	int 	i;

	i = 0;
	if ((*gen)->cmd->heredoc)
		while ((*gen)->cmd->heredoc[i++]);
	else
		(*gen)->cmd->heredoc = malloc(sizeof (char**));
	(*gen)->cmd->heredoc[i] = malloc(sizeof (char) * ft_strlenMS(hereDoc));
	(*gen)->cmd->heredoc[i] = ft_strdup(hereDoc);
}