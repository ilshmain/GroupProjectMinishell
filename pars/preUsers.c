#include "mslib.h"

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

char *preUseFncRedir(char *line, int *i, t_gnrl **gen)
{
	char	*tmp;

	tmp = ft_strdup(line);
	if (tmp[*i] == '>' && tmp[*i + 1] == '>')
		tmp = fnc_redir(tmp, i, gen, 1);
	if (tmp[*i] == '>')
		tmp = fnc_redir(tmp, i, gen, 2);
	if (tmp[*i] == '<' && tmp[*i + 1] == '<')
		tmp = fnc_redir(tmp, i, gen, 3);
	if (tmp[*i] == '<')
		tmp = fnc_redir(tmp, i, gen, 4);
	free (line); // задекоментить, когда будет изменяться лайн (удаляться символы редиров)
	return (tmp);
}