#include "../../include/minishell.h"

char **clear_envp(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (NULL);
}

_Noreturn void exefnc(char **line, t_gnrl **gen)
{
	while (1)
	{
		(*gen)->env = env((*gen)->ptr);
		(*gen)->errors = 0;
		*line = readline("minishell$ ");
		if (*line == NULL)
			error_call("exit\n");
		add_history(*line);
		*line = initLine(*line);
		if (first_fnc(line, gen, 0) == 0)
		{
			(*gen)->cmd = preLogicWork(&(*gen)->cmd);
			if ((*gen)->errors == 0 && (*gen)->cmd != NULL)
				logica(gen);
		}
		(*gen)->env = clear_envp((*gen)->env);
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
			return (NULL);
	return ((*cmd));
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
			line[0] = pre_use_fnc_pipe(line[0], &i, &(*gen)->cmd);
		else
			i++;
	}
	if ((*gen)->errors != 1)
		pre_use_fnc_pipe(line[0], &i, &(*gen)->cmd);
	if ((*gen)->cmd == NULL)
		(*gen)->errors = 1;
	return ((*gen)->errors);
}

char	*pre_use_fnc_pipe(char *line, int *where_is_pipe, t_cmnd **command_line)
{
	char	*tmp;
	t_cmnd	*tmp_command_line;

	if_pipe(command_line, &tmp_command_line, where_is_pipe, line);
	if (line[*where_is_pipe] == '|')
		(*command_line)->flg_pipe = 1;
	tmp_command_line = *command_line;
	if (tmp_command_line->nextList != NULL)
		while (tmp_command_line->nextList != NULL)
			tmp_command_line = tmp_command_line->nextList;
	if (tmp_command_line->command_array != NULL)
	{
		tmp_command_line->nextList = ft_lstnewMS();
		tmp_command_line->flg_pipe = 1;
		tmp_command_line = tmp_command_line->nextList;
	}
	tmp = ft_substrMS(line, 0, *where_is_pipe);
	tmp_command_line->command_array = ft_split(tmp, ' ');
	butilsProv(&tmp_command_line);
	free(tmp);
	tmp = ft_substrMS(line, *where_is_pipe + 1, ft_strlenMS(line) - *where_is_pipe);
	if (tmp && ft_strcmpMS(tmp, "") != 0)
		tmp_command_line->nextList = ft_lstnewMS();
	*where_is_pipe = 0;
	free(line);
	return (tmp);
}

char	*pre_use_substr(char *s, unsigned int start, size_t len)
{
	char	*tmp;

	tmp = ft_substrMS(s, start, len);
	free(s);
	return (tmp);
}

void	if_pipe(t_cmnd **command_line, t_cmnd **tmp_command_line, int *w_i_p, char *line)
{
	(*tmp_command_line) = *command_line;
	if ((*tmp_command_line)->nextList != NULL)
		while ((*tmp_command_line)->nextList != NULL)
			(*tmp_command_line) = (*tmp_command_line)->nextList;
		if (line[*w_i_p] == '|')
			(*tmp_command_line)->flg_pipe = 1;
		if ((*tmp_command_line)->command_array != NULL)
		{
			(*tmp_command_line)->nextList = ft_lstnewMS();
			(*tmp_command_line)->flg_pipe = 1;
			(*tmp_command_line) = (*tmp_command_line)->nextList;
		}
}

char	*cut_spaces(char *line)
{
	int 	i;
	char	*tmp;

	i = 0;
	while (line[i] == ' ')
		i++;
	tmp = ft_substrMS(line, i, ft_strlen(line) - i);
	i = ft_strlenMS(tmp) - 1;
	while (tmp[i] == ' ')
		i--;
	free(line);
	line = ft_substrMS(tmp, 0, i + 1);
	free(tmp);
	return (line);
}