#include "../../include/minishell.h"

void	ft_perror(char *str)
{
	perror(str);
	exit (0);
}

void	create_pipe(t_map *st, int len, char **heredoc)
{
	int	i;

	i = 0;
	st->sum_lst = len;
	if (st->sum_lst > 1 || heredoc != 0)
	{
		while (i < len - 1)
		{
			if (pipe(st[i].fd) == -1)
				ft_perror("Error pipe");
			i++;
		}
	}
}
