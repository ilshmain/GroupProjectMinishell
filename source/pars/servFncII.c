#include "../../include/minishell.h"

void	pLWinWhile(t_cmnd **tmp, t_cmnd **tmp2)
{
	if ((*tmp)->err == 1)
	{
		if ((*tmp)->next_list)
			(*tmp2)->next_list = (*tmp)->next_list;
		else
			(*tmp2)->next_list = NULL;
		free (*tmp);
		(*tmp) = (*tmp2)->next_list;
	}
	else
	{
		*tmp2 = *tmp;
		*tmp = (*tmp)->next_list;
	}
}

char	*initLine(char *line)
{
	char	*tmp;

	tmp = ft_strdup(line);
	free(line);
	return (tmp);
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

int	dual_array_len(char **array)
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