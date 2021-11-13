#include "../../include/minishell.h"

void exefnc(char **line, t_gnrl **gen)
{
	while (1)
	{
		(*gen)->errors = 0;
		*line = readline("minishell$ ");
		if (*line == NULL)
			error_call("exit\n");
		add_history(*line);
		getHistoryLog(*line, (*gen));
		*line = initLine(*line);
		if (first_fnc(line, gen, 0) == 0)
		{
			(*gen)->cmd = preLogicWork(&(*gen)->cmd);
		if ((*gen)->errors == 0 && (*gen)->cmd != NULL)
			fncMonitor((*gen)->cmd);
			if ((*gen)->errors == 0 && (*gen)->cmd != NULL)
				logica(gen);
		}
	}
}

t_cmnd	*preLogicWork(t_cmnd **cmd)
{
	t_cmnd	*tmp;
	t_cmnd	*tmp2;

	tmp = *cmd;
	tmp2 = *cmd;
	if (tmp->nextList != NULL)
		while (tmp->nextList != NULL)
			pLWinWhile(&tmp, &tmp2);
	else if (tmp->nextList == NULL && tmp->err == 1)
	{
		printf("%s\n", tmp->errContext);
		return (NULL);
	}
	return ((*cmd));
}

void	getHistoryLog(char *line, t_gnrl *gen)
{
	char *nameFile;

	if (getenv("SHLVL"))
	{
		nameFile = ft_strjoinMS(".history_log_lvl_", getenv("SHLVL"));
		nameFile = preUseStrJoin(nameFile, ".txt");
	}
	else
		nameFile = ft_strjoin(".history_log_lvl_", ".txt");
	if (line && line[0] != '\0')
	{
		gen->historyLog = open(nameFile, O_WRONLY | O_CREAT | O_APPEND,
								  0644);
		ft_putstr_fd(line, gen->historyLog);
		ft_putstr_fd("\n", gen->historyLog);
		close(gen->historyLog);
	}
	free(nameFile);
}

int	first_fnc(char **line, t_gnrl **gen, int i)
{
	(*gen)->cmd = ft_lstnewMS();
	if (ft_strcmpMS(*line, "") == 0)
		return (1);
	while (line[0][i])
	{
		if (line[0][i] == '\'')
			line[0] = preUseFncQuot(line[0], &i, gen);
		else if (line[0][i] == '\\')
			line[0] = fnc_bslsh(line[0], &i, gen);
		else if (line[0][i] == '\"')
			line[0] = preUseFncDQuot(line, &i, (*gen)->env, gen);
		else if (line[0][i] == '$')
			line[0] = preUseFncDollar(line[0], &i, (*gen)->env);
		else if (line[0][i] == '>' || line[0][i] == '<')
			line[0] = preUseFncRedir(line, &i, gen);
		else if (line[0][i] == '|')
			line[0] = preUseFncPipe(line[0], &i, &(*gen)->cmd);
		else
			i++;
	}
	if ((*gen)->errors != 1)
		preUseFncPipe(line[0], &i, &(*gen)->cmd);
//	fncMonitor((*gen)->cmd);
	if ((*gen)->cmd == NULL)
		(*gen)->errors = 1;
	return ((*gen)->errors);
}

char	*preUseFncPipe(char *line, int *whereIsPipe, t_cmnd **commandLine)
{
	char	*tmp;
	t_cmnd	*tmpCommandline;

	if (line[*whereIsPipe] == '|')
		(*commandLine)->flg_pipe = 1;
	tmpCommandline = *commandLine;
	if (tmpCommandline->nextList != NULL)
		while (tmpCommandline->nextList != NULL)
			tmpCommandline = tmpCommandline->nextList;
	if (tmpCommandline->command_array != NULL)
	{
		tmpCommandline->nextList = ft_lstnewMS();
		tmpCommandline->flg_pipe = 1;
		tmpCommandline = tmpCommandline->nextList;
	}
	tmp = ft_substrMS(line, 0, *whereIsPipe);
	tmpCommandline->command_array = ft_split(tmp, ' ');
	butilsProv(&tmpCommandline);
	free(tmp);
	tmp = ft_substrMS(line, *whereIsPipe + 1, ft_strlenMS(line) - *whereIsPipe);
	if (tmp && ft_strcmpMS(tmp, "") != 0)
		tmpCommandline->nextList = ft_lstnewMS();
	*whereIsPipe = 0;
	free(line);
	return (tmp);
}

