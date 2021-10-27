#include "./pars/mslib.h"
# include <stdio.h>

int main(int argc, char const *argv[], char **envp) {
	(void)argc;
	(void)argv;
	char	*line;
	t_gnrl	*gen;
//	int history;

	gen = malloc(sizeof (t_gnrl));
//	genInit(&gen);
	gen->env = envPrisv(envp);
	initialEnv(envp, &gen->ptr, 0);
	exefnc(&line, &gen);
	return 0;
}

void exefnc(char **line, t_gnrl **gen)
{
	while (1)
	{
		(*gen)->errors = 0;
		*line = readline("minishell$ ");
		add_history(*line);
		if (first_fnc(line, (*gen)->env, gen, 0) == 1)
			printf("there are errors\n");
		else
			logica(gen);
	}
}

char	**envPrisv(char **envp)
{
	return (envp);
}

int	first_fnc(char **line, char **env, t_gnrl **gen, int i)
{
//	line = ft_strdupMS(line);
	(*gen)->cmd = ft_lstnewMS();
	while (line[0][i])
	{
		if (line[0][i] == '\'')
			line[0] = preUseFncQuot(line[0], &i, gen);
		else if (line[0][i] == '\\')
			line[0] = fnc_bslsh(line[0], &i, gen);
		else if (line[0][i] == '\"')
			line[0] = preUseFncDQuot(line[0], &i, env, gen);
		else if (line[0][i] == '$')
			line[0] = preUseFncDollar(line[0], &i, env);
		else if (line[0][i] == '>' || line[0][i] == '<')
			line[0] = preUseFncRedir(line[0], &i, gen);
		else
			i++;
	}
	(*gen)->cmd = fnc_pars(line[0], 0, ft_lstnewMS());
	if ((*gen)->cmd == NULL)
		(*gen)->errors = 1;
	return ((*gen)->errors);
}

char *preUseFncRedir(char *line, int *i, t_gnrl **gen)
{
	char	*tmp;

	if (line[*i] == '>' && line[*i + 1] == '>')
		tmp = fnc_redir(line, i, gen, 1);
	if (line[*i] == '>')
		tmp = fnc_redir(line, i, gen, 2);
	//	if (line[*i] == '<' && line[*i + 1] == '<')
	//		tmp = fnc_redir(line, ++i, gen, 3);
	if (line[*i] == '<')
		tmp = fnc_redir(line, i, gen, 4);
//	free (line); // задекоментить, когда будет изменяться лайн (удаляться символы редиров)
	return (tmp);
}

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
//	else if (ident == 3)
//		fncRedirHeredoc(line, i, gen);
	else if (ident == 4)
		fncRedirOpen(line, gen, nameFile);
	line = strCutStr(line, *i, nameLen);
	return (line);
}

char *strCutStr(char *inStr, int startOfCut, int endOfCut)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_substrMS(inStr, 0, startOfCut);
	tmp1 = ft_substrMS(inStr, endOfCut, ft_strlen(inStr));
	free (inStr);
	inStr = preUseStrJoin(tmp, tmp1);
	return (inStr);
}

char *fncRedirOpen(char *line, t_gnrl **gen, char *nameFile) //доработать
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
		return (line);
	}
	(*gen)->cmd->fd_open = fd; // записываем дескриптор
	return (line);
}

char *fncRedirWrite(char *line, t_gnrl **gen, char *nameFile)
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
		return (line);
	}
	(*gen)->cmd->fd_write = fd; // записываем дескриптор
	return (line);
}

char *fncRedirReWrite(char *line, t_gnrl **gen, char *nameFile)
{
	int fd;

	if ((*gen)->cmd->fd_write)
		close((*gen)->cmd->fd_write);
	if ((*gen)->cmd->fd_reWrite)
		close((*gen)->cmd->fd_reWrite);//если дескриптора не было, если был, то надо закрыть
	fd = open(nameFile, O_TRUNC); // открываем на перезапись
	if (fd == -1) //если файла не существует, создаём
		fd = open(nameFile, O_CREAT);
	if (fd == -1)
	{
		(*gen)->errors = 1;//ОШИППППКИ)
		return (line);
	}
	(*gen)->cmd->fd_reWrite = fd; // записываем дескриптор
	return (line);
}

//t_cmnd	*fnc_pars(char *line, int beginOfLine, t_cmnd *commandLine)
//{
//	int i;
//	int k;
//
//	i = 0;
//	while (line[i] && line[i] != ' ')
//		i++;
//	commandLine->command_array[0] = ft_substrMS(line, beginOfLine, i - beginOfLine);
//	beginOfLine = i;
//	while (line[i] && line[i] != '|')
//		i++;
//	k = i;
//	if (line[k] == '|' && line[k + 1] != '\0')
//	{
//		while (line[k] == ' ' || line[k] == '|')
//			k++;
//		commandLine->nextList = fnc_pars(&line[k], 0, ft_lstnewMS());
//		commandLine->flg_pipe = 1;
//	}
//	commandLine->command_array[1] = ft_substrMS(line, beginOfLine, i - beginOfLine);
//	commandLine->command_array[1] = fncCutTbl(commandLine->command_array[1]);
//	return (commandLine);
//}

t_cmnd	*fnc_pars(char *line, int beginOfLine, t_cmnd *commandLine)
{
	int i;
	int k;

	i = 0;
	while (line[i] && line[i] != '|')
		i++;
	k = i;
	if (line[k] == '|' && line[k + 1] != '\0')
	{
		while (line[k] == ' ' || line[k] == '|')
			k++;
		commandLine->nextList = fnc_pars(&line[k], 0, ft_lstnewMS());
		commandLine->flg_pipe = 1;
		line = ft_substrMS(line, 0, i);
	}
	commandLine->command_array = ft_split(line, ' ');
	return (commandLine);
}

char	*fncCutTbl(char *str)
{
	int		startOfStr;
	int		endOfStr;
	char	*tmp;

	startOfStr = 0;
	while (str[startOfStr] && ft_isalnum(str[startOfStr]) == 0)
		startOfStr++;
	endOfStr = (int)ft_strlenMS(str);
	while (endOfStr > startOfStr && ft_isalnum(str[endOfStr - 1]) == 0)
		endOfStr--;
	tmp = ft_substr(str, startOfStr, endOfStr - startOfStr);
	free (str);
	return (tmp);
}

t_cmnd	*ft_lstnewMS(void)
{
	t_cmnd *tmp;

	tmp = malloc(sizeof (t_cmnd) * 1);
	tmp->command_array = malloc(sizeof (char*) * 1);
	tmp->flg_pipe = 0;
	tmp->fd_reWrite = 0;
	tmp->fd_write = 0;
	tmp->fd_open = 0;
	tmp->heredoc = NULL;
	tmp->nextList = NULL;
	return (tmp);
}


// //////////////////////  PreUsers  ////////////////////////////////

char	*preUseFncDollar(char *line, int *i, char **env)
{
	char	*tmp;

	tmp = fnc_dollar(line, i, env);
	free (line);
	return (tmp);
}

char	*preUseFncDQuot(char *line, int *i, char **env, t_gnrl **gen)
{
	char	*tmp;

	tmp = fnc_dquot(line, i, env, gen);
	free (line);
	return (tmp);
}

char	*preUseFncQuot(char *line, int *i, t_gnrl **gen)
{
	char	*tmp;

	tmp = fnc_quot(line, i, gen);
	free (line);
	return (tmp);
}

char	*preUseStrJoin(char *str1, char *str2)
{
	char *tmp;

	tmp = ft_strjoinMS(str1, str2);
	free (str1);
	return (tmp);
}
// //////////////////////  PreUsers  ////////////////////////////////

//char    *ft_strmapi(char const *s, char (*f)(unsigned int, char))
//{
//	size_t  i;
//	char    *res;
//
//	if (s == NULL || f == NULL)
//		return (NULL);
//	res = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
//	if (res == NULL)
//		return (NULL);
//	i = 0;
//	while (s[i])
//	{
//
//		res[i] = f(i, s[i]);
//		i++;
//	}
//	res[i] = '\0';
//	return (res);
//}

char	*fnc_quot(char *line, int *i, t_gnrl **gen)
{
	int j;

	j = *i;
	while (line[++*i])
	{
		if (line[*i] == '\'')
			break ;
	}
	if (line[*i] == '\0')
	{
		(*gen)->errors = 1;
		i++;
		return (line);
	}
	return (unionForQuotStr(line, i, j));
}

char	*fnc_dquot(char *line, int *i, char **env, t_gnrl **gen)
{
	int j;

	j = *i;
	while (line[++*i])
	{
		if (line[*i] == '\\' && (line[*i + 1] == '\"' || line[*i + 1] == '$' ||
		line[*i + 1] == '\\'))
			line = fnc_bslsh(line, i, gen);
		if (line[*i] == '$')
			line = preUseFncDollar(line, i, env);
		if (line[*i] == '\"')
			break ;
	}
	if (line[*i] == '\0')
		(*gen)->errors = 1;
	return (unionForQuotStr(line, i, j));
}

char	*unionForQuotStr(char *line, int *i, int j)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substrMS(line, 0, j);
	tmp2 = ft_substrMS(line, j + 1, *i - j - 1);
	tmp1 = preUseStrJoin(tmp1, tmp2);
	free (tmp2);
	tmp2 = ft_strdupMS(line + *i + 1);
	tmp1 = preUseStrJoin(tmp1, tmp2);
	if (ft_strcmpMS(tmp2, "\0") != 0)
		free(tmp2);
	--*i;
	return (tmp1);
}

int	ifKeyForFnsDollar(char c)
{
	if (c == '_' || ft_isalnumMS(c))
		return (1);
	return (0);
}

char	*fnc_dollar(char *line, int *i, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	j = *i;
	while (line[++(*i)])
		if (!ifKeyForFnsDollar(line[*i]))
			break ;
	if (*i == j + 1)
		return (line);
	tmp2 = dollarAssigment(line, i, j, env);
	tmp = ft_substrMS(line, 0, j);
	tmp = preUseStrJoin(tmp, tmp2);
	free(tmp2);
	tmp2 = ft_strdupMS(line + *i);
	tmp = preUseStrJoin(tmp, tmp2);
	free(tmp2);
	return (tmp);
}

char	*dollarAssigment(char *line, int *i, int j, char **env)
{
	char	*tmp;
	char	*tmp2;
	int		z;
	int		k;

	tmp = ft_substrMS(line, j + 1, *i - j - 1);
	z = -1;
	k = 0;
	while (env[++z])
	{
		if (ft_strnstrMS(env[z], tmp, ft_strlenMS(tmp)))
		{
			k = 0;
			while (env[z][k] && env[z][k] != '=')
				k++;
			tmp2 = ft_substrMS(env[z], 0, k);
			if (ft_strcmpMS(tmp, tmp2) == 0)
				break ;
		}
	}
	free (tmp2);
	tmp2 = ft_substrMS(env[z], k + 1, ft_strlenMS(env[z]) - k);
	free (tmp);
	return (tmp2);
}

char	*fnc_bslsh(char *line, int *i, t_gnrl **gen)
{
	char *tmp1;
	char *tmp2;

	tmp2 = NULL;
	if (ft_strcmpMS(line + *i + 1, "\0") == 0)
		(*gen)->errors = 1;
	if (*i == 0)
		tmp1 = ft_strdupMS(line + *i + 1);
	if (*i > 0)
	{
		tmp1 = ft_substrMS(line, 0, *i);
		tmp2 = ft_strdupMS(line + *i + 1);
		tmp1 = preUseStrJoin(tmp1, tmp2);
	}
	++(*i);
	free (line);
	free (tmp2);
	return (tmp1);
}

int	ft_double_vlm(char *str, char key)
{
	int i;
	int	qt;

	i = 0;
	qt = 0;
	while (str[i])
	{
		if (str[i] == key && qt == 0)
			qt++;
		else if (str[i] == key && qt == 1)
			qt--;
		i++;
	}
	if (qt == 0)
		return (0);
	else
		return (1);
}

void	ft_putstr_fdMS(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
