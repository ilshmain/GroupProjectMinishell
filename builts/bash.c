#include "../include/minishell.h"

// bash BUILT*****************************

void	levelUpBash(t_list *ptr)
{
	char	*buf;
	int		i;

	while (ptr)
	{
		if (ft_strncmp(ptr->str, "SHLVL=", 6) == 0)
		{
			buf = change_ft_strrchr(ptr->str, '=');
			i = ft_atoi(buf);
			i++;
			ptr->str = ft_strjoin("SHLVL=", ft_itoa(i));
		}
		ptr = ptr->next;
	}
}
//**************************************