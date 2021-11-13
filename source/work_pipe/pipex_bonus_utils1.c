#include "../../include/minishell.h"

int	ft_perror(char *str)
{
	perror(str);
	return (1);
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
