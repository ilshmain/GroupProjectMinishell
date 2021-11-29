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
		check_redirect((*zik)->cmd);
		dup_relize((*zik)->cmd);
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
		cmd = cmd->next_list;
	}
	return (i);
}

void	close_read_and_write(t_cmnd *start)
{
	while (start)
	{
		if (start->fd_open > 0)
			close(start->fd_open);
		if (start->fd_write > 0)
			close(start->fd_write);
		if (start->fd_re_write > 0)
			close(start->fd_re_write);
		start = start->next_list;
	}
}

void	wait_proceses(t_cmnd *start)
{
	t_cmnd	*cmd;
	int		status;

	status = 0;
	cmd = start;
	close_read_and_write(cmd);
	while (start->next_list)
	{
		close(start->fd[0]);
		close(start->fd[1]);
		start = start->next_list;
	}
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		exit_code = WEXITSTATUS(status);
		if (!exit_code && WIFSIGNALED(status))
		{
			exit_code = 128 + WTERMSIG(status);
		}
		cmd = cmd->next_list;
	}
}

int	work_with_pipe(t_gnrl **zik)
{
	t_cmnd	*start;
	int		len;

	start = (*zik)->cmd;
	len = ft_sum_pipe((*zik)->cmd);
	if (!(*zik)->cmd->next_list && (*zik)->cmd->heredoc == NULL && \
		((*zik)->cmd->fd_write < 0) && ((*zik)->cmd->fd_re_write < 0))
	{
		if (built_func((*zik), (*zik)->ptr) == 1)
			return (1);
	}
	create_pipe((*zik)->cmd);
	while (len--)
	{
		many_command(zik, start);
		(*zik)->cmd = (*zik)->cmd->next_list;
	}
	wait_proceses(start);
	return (0);
}
