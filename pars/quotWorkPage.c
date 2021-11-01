#include "mslib.h"

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
		*i += 1;
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
