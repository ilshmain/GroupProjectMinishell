#include "../../include/minishell.h"

char	*fnc_bslsh(char *line, int *i, t_gnrl **gen)
{
	char *tmp1;
	char *tmp2;

	tmp2 = NULL;
	if (ft_strcmpMS(line + *i + 1, "\0") == 0)
	{
		(*gen)->errors = 1;
		*i += 1;
		return (line);
	}
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
	if (tmp2)
		free (tmp2);
	return (tmp1);
}