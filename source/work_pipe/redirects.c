#include "../../include/minishell.h"

int CheckRedirRead(t_cmnd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_open > 0)
			cmd->in = cmd->fd_open;
		cmd = cmd->next_list;
	}
	return (1);
}

int CheckRedirWrite(t_cmnd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_write > 0)
			cmd->out = cmd->fd_write;
		cmd = cmd->next_list;
	}
	return (1);
}

int CheckRedirRewrite(t_cmnd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_re_write > 0)
			cmd->out = cmd->fd_re_write;
		cmd = cmd->next_list;
	}
	return (1);
}

int	check_redirect(t_cmnd *cmd)
{
	while (cmd)
	{
		if (cmd->heredoc != NULL)
			check_heredoc(cmd->heredoc, cmd);
		if (cmd->fd_open > 0)
			CheckRedirRead(cmd);
		if (cmd->fd_write > 0)
			CheckRedirWrite(cmd);
		if (cmd->fd_re_write > 0)
			CheckRedirRewrite(cmd);
		cmd = cmd->next_list;
	}
	return (1);
}