#include "mslib.h"

char *fnc_redir(char **line, int *i, t_gnrl **gen, int ident)
{
	int nameLen;
	char *nameFile;

	nameFile = nameForRedir(line, &nameLen, i, gen);
	while (line[0][nameLen] && line[0][nameLen] == ' ') // пропускаем лишние пробелы
		nameLen++;
	if (ident == 1)
		fncRedirWrite(line[0], gen, nameFile);
	else if (ident == 2)
		fncRedirReWrite(line[0], gen, nameFile);
	else if (ident == 3)
		fncRedirHeredoc(gen, nameFile);
	else if (ident == 4)
		fncRedirOpen(line[0], gen, nameFile);
	free (nameFile);
	line[0] = strCutStr(line[0], *i, nameLen);
	return (line[0]);
}

char	*nameForRedir(char **line, int *nameLen, int *i, t_gnrl **gen)
{
	char	*fileName;

	*nameLen = *i;
	while ((line[0][*nameLen]) && (ft_isalnumMS(line[0][*nameLen]) == 0)) // пропускаем символы, которые не могут входить в нейминг
		*nameLen += 1;
	line[0] = strCutStr(*line, *i, *nameLen);
//	*nameLen = *i;
//	*i = *nameLen;
	while ((line[0][*nameLen]) && (line[0][*nameLen] != '|' || line[0][*nameLen] != '>' || line[0][*nameLen] != '<')) // пропускаем символы, которые не могут входить в нейминг
		{
		if (line[0][*nameLen] == '\'')
			line[0] = preUseFncQuot(line[0], nameLen, gen);
		else if (line[0][*nameLen] == '\\')
			line[0] = fnc_bslsh(line[0], nameLen, gen);
		else if (line[0][*nameLen] == '\"')
			line[0] = preUseFncDQuot(line[0], nameLen, (*gen)->env, gen);
		else if (line[0][*nameLen] == '$')
			line[0] = preUseFncDollar(line[0], nameLen, (*gen)->env);
		*nameLen += 1;
		//		printf("%c\n", line[0][*nameLen]);
		}
	fileName = ft_substr(line[0], *i, *nameLen - *i);// берём имя
	return (fileName);
}

//char	*ifName(char **line, int *i, t_gnrl **gen)
//{
//
//	if (line[0][*i] == '\'')
//		line[0] = preUseFncQuot(line[0], i, gen);
//	else if (line[0][*i] == '\\')
//		line[0] = fnc_bslsh(line[0], i, gen);
//	else if (line[0][*i] == '\"')
//		line[0] = preUseFncDQuot(line[0], i, (*gen)->env, gen);
//	else if (line[0][*i] == '$')
//		line[0] = preUseFncDollar(line[0], i, (*gen)->env);
//	else if (line[0][*i] == '>' || line[0][*i] == '<')
//		line[0] = preUseFncRedir(line[0], i, gen);
//	else if (line[0][*i] == '|')
//		line[0] = preUseFncPipe(line[0], i, &(*gen)->cmd);
//	else
//		*i += 1;
//	return (*line);
//}

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