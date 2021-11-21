#include "../../include/minishell.h"

void	ft_perror_2(char *str)
{
	perror(str);
	free(str);
}

void	ft_perror(char *str)
{
	perror(str);
	exit (0);
}

void	create_pipe(t_cmnd *cmd)
{
	while (cmd->nextList)
	{
		if (pipe(cmd->fd) < 0)
			ft_perror("Error pipe");
		cmd->out = cmd->fd[1];
		cmd->nextList->in = cmd->fd[0];
		cmd = cmd->nextList;
	}
}
