/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:18:33 by fmint             #+#    #+#             */
/*   Updated: 2021/11/29 17:18:35 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_redir_read(t_cmnd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_open > 0)
			cmd->in = cmd->fd_open;
		cmd = cmd->next_list;
	}
	return (1);
}

int	check_redir_write(t_cmnd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_write > 0)
			cmd->out = cmd->fd_write;
		cmd = cmd->next_list;
	}
	return (1);
}

int	check_redir_rewrite(t_cmnd *cmd)
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
			check_redir_read(cmd);
		if (cmd->fd_write > 0)
			check_redir_write(cmd);
		if (cmd->fd_re_write > 0)
			check_redir_rewrite(cmd);
		cmd = cmd->next_list;
	}
	return (1);
}
