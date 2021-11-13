#include "../../include/minishell.h"

int	Dup(t_cmnd *cmd)
{
	if (cmd->in != STDIN_FILENO)
	{
		if (dup2(cmd->in, STDIN_FILENO) < 0)
			return (1);
		close(cmd->in);
	}
	if (cmd->out != STDOUT_FILENO)
	{
		if (dup2(cmd->out, STDOUT_FILENO) < 0)
			return (1);
		close(cmd->out);
	}
	return (0);
}

int CheckRedirRead(t_cmnd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_open > 0)
			cmd->in = cmd->fd_open;
		cmd = cmd->nextList;
	}
	return (1);
}

int CheckRedirWrite(t_cmnd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_write > 0)
			cmd->out = cmd->fd_write;
		cmd = cmd->nextList;
	}
	return (1);
}

int CheckRedirRewrite(t_cmnd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_reWrite > 0)
			cmd->out = cmd->fd_reWrite;
		cmd = cmd->nextList;
	}
	return (1);
}

int	CheckRedirect(t_cmnd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_open > 0)
			CheckRedirRead(cmd);
//		if (cmd->heredoc != NULL)
//			CheckRedirHeredoc(cmd);
		if (cmd->fd_write > 0)
			CheckRedirWrite(cmd);
		if (cmd->fd_reWrite > 0)
			CheckRedirRewrite(cmd);
		cmd = cmd->nextList;
	}
	return (1);
}