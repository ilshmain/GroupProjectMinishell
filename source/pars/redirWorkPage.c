#include "../../include/minishell.h"

char *fnc_redir(char **line, int *i, t_gnrl **gen, int ident)
{
	int		nameLen;
	char	*nameFile;
	t_cmnd	*tmpCmd;

	tmpCmd = (*gen)->cmd;
	while (tmpCmd->nextList != NULL)
		tmpCmd = tmpCmd->nextList;
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

char	*nameForRedir(char **line, int *nameLen, int *i, t_gnrl **gen)
{
	char	*fileName;

	*nameLen = *i;
	while ((line[0][*nameLen]) && (ft_isalnumMS(line[0][*nameLen]) == 0)) // пропускаем символы, которые не могут входить в нейминг
		*nameLen += 1;
	line[0] = strCutStr(*line, *i, *nameLen);
	*nameLen = *i;
	while ((line[0][*nameLen])) // пропускаем символы, которые не могут входить в нейминг
		{
		if (line[0][*nameLen] == '\'')
			line[0] = preUseFncQuot(line[0], nameLen, gen);
		else if (line[0][*nameLen] == '\\')
			line[0] = fnc_bslsh(line[0], nameLen, gen);
		else if (line[0][*nameLen] == '\"')
			line[0] = preUseFncDQuot(line, nameLen, (*gen)->env, gen);
		else if (line[0][*nameLen] == '$')
			line[0] = preUseFncDollar(line[0], nameLen, (*gen)->env);
		else if (line[0][*nameLen] == '|' || line[0][*nameLen] == '<' ||
		line[0][*nameLen] == '>' || line[0][*nameLen] == ' ')
			break;
		*nameLen += 1;
		}
	fileName = ft_substr(line[0], *i, *nameLen - *i);// берём имя
	return (fileName);
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
		(*cmd)->errContext = ft_strjoinMS(nameFile, ": file does not exist or access is denied");
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
		(*cmd)->fd_write = -2;
	}
	if ((*cmd)->fd_reWrite > 0)
	{
		close((*cmd)->fd_reWrite);
		(*cmd)->fd_reWrite = -2;
	}//если дескриптора не было, если был, то надо закрыть
	fd = open(nameFile, O_WRONLY | O_CREAT | O_APPEND); // открываем на дозапись
	if (fd == -1)
	{
		(*cmd)->err = 1;
		(*cmd)->errContext = ft_strjoinMS(nameFile, ": file does not exist or access is denied");
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
		(*cmd)->fd_write = -2;
	}
	if ((*cmd)->fd_reWrite > 0)
	{
		close((*cmd)->fd_reWrite);
		(*cmd)->fd_reWrite = -2;
	}//если дескриптора не было, если был, то надо закрыть
	fd = open(nameFile, O_RDWR | O_CREAT | O_TRUNC); // открываем на перезапись
	if (fd == -1)
	{
		(*cmd)->err = 1;//ОШИППППКИ)
		(*cmd)->errContext = ft_strjoinMS(nameFile, ": Permission denied");
		return ;
	}
	(*cmd)->fd_reWrite = fd; // записываем дескриптор
}

void	fncRedirHeredoc(t_cmnd **cmd, char *hereDoc)
{
	int 	i;
	char	**tmp;

	i = 0;
	if ((*cmd)->fd_open > 0)
	{
		close((*cmd)->fd_open);
		(*cmd)->fd_open = -2;
	}
	if ((*cmd)->heredoc)
		tmp = malloc(sizeof (char **) * (dualArrayLen((*cmd)->heredoc) + ft_strlenMS(hereDoc)));
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

int	dualArrayLen(char **array)
{
	int	i;
	int	j;
	int	len;

	if (array == NULL)
		return (0);
	i = 0;
	j = 0;
	len = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
			j++;
		len += j;
		i++;
	}
	return (len);
}
