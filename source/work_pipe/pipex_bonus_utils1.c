#include "../../include/minishell.h"

void	ft_perror(char *str)
{
	perror(str);
	exit (0);
}

void	create_pipe(t_cmnd *cmd)
{
	while (cmd->next_list)
	{
		if (pipe(cmd->fd) < 0)
			ft_perror("Error pipe");
		cmd->out = cmd->fd[1];
		cmd->next_list->in = cmd->fd[0];
		cmd = cmd->next_list;
	}
}
