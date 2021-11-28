/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 20:00:08 by fmint             #+#    #+#             */
/*   Updated: 2021/11/27 20:00:11 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	many_command(t_gnrl **zik, t_cmnd *start)
{
	(*zik)->cmd->pid = fork();
	(*zik)->cmd->fork = 1;
	if ((*zik)->cmd->pid == -1)
		ft_perror("Error pid(fork)+");
	if ((*zik)->cmd->pid == 0)
	{
		CheckRedirect((*zik)->cmd);
		Dup((*zik)->cmd);
		pid_children(zik, start);
	}
	return (1);
}

int	ft_sum_pipe(t_cmnd *cmd)
{
	int	i;

	i = 0;
	while (cmd != NULL)
	{
		i++;
		cmd->in = STDIN_FILENO;
		cmd->out = STDOUT_FILENO;
		cmd->fd[0] = 0;
		cmd->fd[1] = 0;
		cmd = cmd->nextList;
	}
	return (i);
}

void  close_read_and_write(t_cmnd *start)
{
	while (start)
	{
		if (start->fd_open > 0)
			close(start->fd_open);
		if (start->fd_write > 0)
			close(start->fd_write);
		if (start->fd_reWrite > 0)
			close(start->fd_reWrite);
		start = start->nextList;
	}
}

void	wait_proceses(t_cmnd *start)
{
	t_cmnd	*cmd;
	int		status;

	status = 0;
	cmd = start;
	close_read_and_write(cmd);
	while (start->nextList)
	{
		close(start->fd[0]);
		close(start->fd[1]);
		start = start->nextList;
	}
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		exit_code = WEXITSTATUS(status);
		if (!exit_code && WIFSIGNALED(status))
		{
			exit_code = 128 + WTERMSIG(status);
		}
		cmd = cmd->nextList;
	}
}

int	work_with_pipe(t_gnrl **zik)
{
	t_cmnd	*start;
	int		len;

	start = (*zik)->cmd;
	len = ft_sum_pipe((*zik)->cmd);
	if (!(*zik)->cmd->nextList && (*zik)->cmd->heredoc == NULL)
	{
		if (built_func((*zik), (*zik)->ptr) == 1)
			return (1);
	}
	create_pipe((*zik)->cmd);
	while (len--)
	{
		many_command(zik, start);
		(*zik)->cmd = (*zik)->cmd->nextList;
	}
	wait_proceses(start);
	return (0);
}
