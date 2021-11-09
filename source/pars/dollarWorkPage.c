#include "../../include/minishell.h"

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
	if (tmp != NULL && tmp2 != NULL)
		tmp = preUseStrJoin(tmp, tmp2);
	free(tmp2);
	tmp2 = NULL;
	if (line[*i] != '\0')
	{
		tmp2 = ft_strdupMS(line + *i);
		tmp = preUseStrJoin(tmp, tmp2);
	}
	if (tmp2 != NULL)
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
	if (tmp2 != NULL)
		free (tmp2);
	tmp2 = ft_substrMS(env[z], k + 1, ft_strlenMS(env[z]) - k);
	free (tmp);
	return (tmp2);
}