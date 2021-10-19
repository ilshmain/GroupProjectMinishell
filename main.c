#include "mslib.h"
# include <stdio.h>

int main(int argc, char const *argv[], char **envp) {
	(void)argc;
	(void)argv;
	char	*line;
	t_gnrl	*gen;

	gen = malloc(sizeof (gen));
	while (1)
	{
		gen->errors = 0;
		line = readline("minishell$ ");
		add_history(line);
		if (first_fnc(&line, envp, &gen) == 1)
			printf("there are errors\n");
		// free(line);
	}
	return 0;
}

int	first_fnc(char **line, char **env, t_gnrl **gen)
{
	int	i;

	i = 0;
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
		else
			i++;
	}
//	printf("%s\n", line[0]);
	(*gen)->cmd = fnc_pars(line[0], 0, ft_lstnew());
	printf("1 array command: %s\n", (*gen)->cmd->command_array[0]);
	printf("1 array arg: %s\n", (*gen)->cmd->command_array[1]);
	printf("1 array flgpipe: %d\n", (*gen)->cmd->flg_pipe);
	// printf("2 array command: %s\n", (*gen)->cmd->nextList->command_array[0]);
	// printf("2 array arg: %s\n", (*gen)->cmd->nextList->command_array[1]);
	// printf("2 array flgpipe: %d\n", (*gen)->cmd->nextList->flg_pipe);
	// printf("3 array command: %s\n", (*gen)->cmd->nextList->nextList->command_array[0]);
	// printf("3 array arg: %s\n", (*gen)->cmd->nextList->nextList->command_array[1]);
	// printf("3 array flgpipe: %d\n", (*gen)->cmd->nextList->nextList->flg_pipe);
	return ((*gen)->errors);
}

t_cmnd	*fnc_pars(char *line, int beginOfLine, t_cmnd *commandLine)
{
	int i;

	i = 0;
	while (line[i] != ' ')
		i++;
	commandLine->command_array[0] = ft_substr(line, beginOfLine, i - beginOfLine);
	beginOfLine = i;
	while (line[beginOfLine] == ' ')
		beginOfLine++;
	while (line[i] && line[i] != '|')
		i++;
	if (line[i] == '|')
	{
		int k;

		k = i;
		while (line[k] == ' ' || line[k] == '|')
			k++;
		commandLine->nextList = fnc_pars(&line[k], 0, ft_lstnew());
		commandLine->flg_pipe = 1;
	}
	commandLine->command_array[1] = ft_substr(line, beginOfLine, i - beginOfLine);
	return (commandLine);
}

t_cmnd	*ft_lstnew(void)
{
	t_cmnd *tmp;

	tmp = malloc(sizeof (t_cmnd));
	tmp->command_array = malloc(sizeof (char*));
	tmp->flg_pipe = 0;
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

	tmp = ft_strjoin(str1, str2);
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

	tmp1 = ft_substr(line, 0, j);
	tmp2 = ft_substr(line, j + 1, *i - j - 1);
	tmp1 = preUseStrJoin(tmp1, tmp2);
	free (tmp2);
	tmp2 = ft_strdup(line + *i + 1);
	tmp1 = preUseStrJoin(tmp1, tmp2);
	if (ft_strcmp(tmp2, "\0") != 0)
		free(tmp2);
	--*i;
	return (tmp1);
}

int	ifKeyForFnsDollar(char c)
{
	if (c == '_' || ft_isalnum(c))
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
	tmp = ft_substr(line, 0, j);
	tmp = preUseStrJoin(tmp, tmp2);
	free(tmp2);
	tmp2 = ft_strdup(line + *i);
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

	tmp = ft_substr(line, j + 1, *i - j - 1);
	z = -1;
	k = 0;
	while (env[++z])
	{
		if (ft_strnstr(env[z], tmp, ft_strlen(tmp)))
		{
			k = 0;
			while (env[z][k] && env[z][k] != '=')
				k++;
			tmp2 = ft_substr(env[z], 0, k);
			if (ft_strcmp(tmp, tmp2) == 0)
				break ;
		}
	}
	free (tmp2);
	tmp2 = ft_substr(env[z], k + 1, ft_strlen(env[z]) - k);
	free (tmp);
	return (tmp2);
}

char	*fnc_bslsh(char *line, int *i, t_gnrl **gen)
{
	char *tmp1;
	char *tmp2;

	tmp2 = NULL;
	if (ft_strcmp(line + *i + 1, "\0") == 0)
		(*gen)->errors = 1;
	if (*i == 0)
		tmp1 = ft_strdup(line + *i + 1);
	if (*i > 0)
	{
		tmp1 = ft_substr(line, 0, *i);
		tmp2 = ft_strdup(line + *i + 1);
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

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
