#include "../../include/minishell.h"

int size_heredoc(char **argv)
{
	int i;
	i = 0;

	while (argv[i])
		i++;
	return (i - 1);
}

void	have_here_doc(t_map *st, char **argv, t_cmnd *cmd)
{
	int		i;
	int		len;
	char	*buf;

	buf = NULL;
	i = 0;
	len = size_heredoc(argv);
	while (argv[i])
	{
		while (ft_strcmp(buf, argv[i]))
		{
			write(1, "heredoc> ", 9);
			if (cmd->fd_open == 0)
			{
				if (get_next_line(0, &buf) && ft_strncmp(buf, argv[i], ft_strlen(argv[i])))
				{
					if (len == i)
					{
						write(st[st->i].fd[1], buf, ft_strlen(buf));
						write(st[st->i].fd[1], "\n", 1);
					}
				}
				free(buf);
			}
		}
		i++;
	}
	exit (0);
}

void	CheckHeredocAndFdread(t_map *st, t_cmnd *cmd)
{
	if (cmd->heredoc != 0)
		st->flag = 1;
	if (cmd->fd_open != 0)
	{
		if (dup2(cmd->fd_open, 0) < 0)
			ft_perror("Couldn't write to the pipe");
	}
}

int	many_command(t_map *st, char **envp, char **argv, t_gnrl **zik)
{
	int 	pid;

	pid = fork();
	if (pid == -1)
		ft_perror("Error pid(fork)");
	if (pid == 0)
	{
//		CheckHeredocAndFdread(st, (*zik)->cmd);
		if (st->flag == 1)
			have_here_doc(st, argv, (*zik)->cmd);
		pid_children(st, envp, zik);
		return (3);
	}
	else
	{
		wait(NULL);
		if (st[st->i].fd[0] != 0 || st[st->i].fd[1] != 0)
		{
			close((st[st->i].fd[1]));
			if (st->i)
			{
				close(st[st->i - 1].fd[1]);
				close(st[st->i - 1].fd[0]);
			}
		}
	}
	return (0);
}

int ft_sum_pipe(t_cmnd *cmd)
{
	int i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->nextList;
	}
	return (i);
}

int	work_with_pipe(t_gnrl **zik)
{
	int len;
	t_map	*st;

	len = ft_sum_pipe((*zik)->cmd);
	st = malloc(sizeof(t_map) * len);
	create_pipe(st, len);
	while ((*zik)->cmd)
	{
		st->flag = 0;
		many_command(st, (*zik)->env, (*zik)->cmd->heredoc, zik);
		st->i++;
		(*zik)->cmd = (*zik)->cmd->nextList;
	}
	free(st);
//	dup2(1, 0);
	return (0);
}
