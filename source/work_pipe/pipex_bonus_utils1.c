#include "../../include/minishell.h"

void	ft_perror(char *str)
{
	perror(str);
	exit (0);
}

void	create_pipe(t_map *st, int sum_list)
{
	int	i;

	i = 0;
	while (i < sum_list - 1)
	{
		if (pipe(st[i].fd) == -1)
			ft_perror("Error pipe");
		i++;
	}
}
