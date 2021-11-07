#include "../../include/minishell.h"

void exefnc(char **line, t_gnrl **gen)
{
	while (1)
	{
		(*gen)->errors = 0;
		*line = readline("minishell$ ");
		if (*line == NULL)
			error_call("kuku exit\n");
		add_history(*line);
//		*line = initLine(*line);
		if (first_fnc(line, gen, 0) == 1)
			printf("there are errors\n");
		else
			logica(gen);
	}
}

char	*initLine(char *line)
{
	char	*tmp;

	tmp = ft_strdupMS(line);
	return (tmp);
}

void	exitCtrlD(void)
{
	printf("zzz exit");
	exit(0);
}

void	ctrl_c_hook(int sgn)
{
	rl_on_new_line();
	rl_redisplay();
	printf("  \n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sgn;
}

int	first_fnc(char **line, t_gnrl **gen, int i)
{
	(*gen)->cmd = ft_lstnewMS();
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
	if ((*gen)->errors == 0)
	{
		preUseFncPipe(line[0], &i, &(*gen)->cmd);
//		fncMonitor((*gen)->cmd);
	}
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

// ДОБАВЛЕНЫ ЧЕКЕРЫ НА НАЛИЧИЕ ПАЙПОВ
//int	check_for_pipes(char const *line)
//{
//	int	i;
//
//	i = 0;
//	while (line[i])
//	{
//		if (line[i] == '|')
//			return (1);
//		i++;
//	}
//	return (0);
//}

//t_cmnd	*fnc_pars(char *line, int beginOfLine, t_cmnd *commandLine)
//{
//	int i;
//	int k;
//
//	i = 0;
//	while (line[i])
//	{
//		if (line[i] == '|')
//			break;
//		else if (line[i] == '<' || line[i] == '>')
//			preUseFncRedir();
//		i++;
//	}
//	k = i;
//	if (line[k] == '|' && line[k + 1] != '\0')
//	{
//		while (line[k] == ' ' || line[k] == '|')
//			k++;
//		commandLine->nextList = fnc_pars(&line[k], 0, ft_lstnewMS());
//		commandLine->flg_pipe = 1;
//		line = ft_substrMS(line, 0, i);
//	}
//	else
	//	commandLine->err = 1;
//	commandLine->command_array = ft_split(line, ' ');
//	butilsProv(&commandLine);
//	fncMonitor(commandLine);
//	return (commandLine);
//}

