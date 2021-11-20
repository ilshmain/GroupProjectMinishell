#include "../../include/minishell.h"

// bash BUILT*****************************

char	*levelUpDown(char *str, int flag_up_down)
{
	char	*lvl;
	char	*buf;
	int		i;

	lvl = NULL;
	buf = change_ft_strrchr(str, '=');
	i = ft_atoi(buf);
	if (flag_up_down == 1)
		i++;
	else
		i--;
	lvl = ft_strjoin("SHLVL=", ft_itoa(i));
	return (lvl);
}
//**************************************

