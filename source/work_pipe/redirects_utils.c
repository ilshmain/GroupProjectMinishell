/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:18:23 by fmint             #+#    #+#             */
/*   Updated: 2021/11/29 17:18:26 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	size_heredoc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i - 1);
}

void	cch_hrd(int sgn)
{
	(void)sgn;
	exit(g_exit_code);
}

void	heredoc(char **argv, t_cmnd *cmd, int i)
{
	int		len;
	char	*buf;

	buf = NULL;
	len = size_heredoc(argv);
	while (argv[i])
	{
		while (ft_strcmp(buf, argv[i]))
		{
			signal(SIGINT, cch_hrd);
			write(1, "> ", 2);
			if (get_next_line(0, &buf) && \
				ft_strncmp(buf, argv[i], ft_strlen(argv[i])))
			{
				if (len == i)
					ft_putendl_fd(buf, cmd->out);
			}
			else
				error_call("");
			free(buf);
		}
		free(argv[i]);
		i++;
	}
	exit (0);
}

void	check_heredoc(char **argv, t_cmnd *cmd)
{
	int	fd[2];
	int	pid;
	int	i;

	i = 0;
	if (pipe(fd) < 0)
		ft_perror("Error pipe");
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		cmd->out = fd[1];
		heredoc(argv, cmd, i);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		cmd->in = fd[0];
	}
}

int	dup_relize(t_cmnd *cmd)
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
