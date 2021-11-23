#include "../../include/minishell.h"

int		exit_built(char	**str, t_list **ptr)
{

	int i;

	i = size_two_poineter_mas(str);
	if (i == 1)
	{
		levelUpDown(str[0], 0);
	}
	return (0);
}