#include "../../include/minishell.h"

//int size_heredoc(char **argv)
//{
//	int i;
//	i = 0;
//
//	while (argv[i])
//		i++;
//	return (i - 1);
//}

//void	have_here_doc(t_map *st, char **argv, t_cmnd *cmd)
//{
//	int		i;
//	int		len;
//	char	*buf;
//
//	buf = NULL;
//	i = 0;
//	len = size_heredoc(argv);
//	while (argv[i])
//	{
//		while (ft_strcmp(buf, argv[i]))
//		{
//			write(1, "heredoc> ", 9);
//			if (cmd->fd_open == 0)
//			{
//				if (get_next_line(0, &buf) && ft_strncmp(buf, argv[i], ft_strlen(argv[i])))
//				{
//					if (len == i)
//					{
//						write(st[st->i].fd[1], buf, ft_strlen(buf));
//						write(st[st->i].fd[1], "\n", 1);
//					}
//				}
//				free(buf);
//			}
//		}
//		i++;
//	}
//	exit (0);
//}

int	many_command(char **envp, t_gnrl **zik, t_cmnd *start)
{
	(*zik)->cmd->pid = fork();
	(*zik)->cmd->fork = 1;
	if ((*zik)->cmd->pid == -1)
		ft_perror("Error pid(fork)+");
	if ((*zik)->cmd->pid == 0)
	{
		CheckRedirect((*zik)->cmd);
		Dup((*zik)->cmd);
		pid_children(envp, zik, start);
	}
	return (1);
}

int ft_sum_pipe(t_cmnd *cmd)
{
	int i = 0;
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

int	work_with_pipe(t_gnrl **zik)
{
	t_cmnd *start;
	int len;

	start = (*zik)->cmd;
	len = ft_sum_pipe((*zik)->cmd);
	if (!(*zik)->cmd->nextList && (*zik)->cmd->heredoc == NULL)
	{
		if (builtFunc((*zik), (*zik)->ptr) == 1)
			return (1);
	}
	create_pipe((*zik)->cmd);
	while (len--)
	{
		many_command((*zik)->env, zik, start);
		(*zik)->cmd = (*zik)->cmd->nextList;
	}
	while (start->nextList)
	{
		close(start->fd[0]);
		close(start->fd[1]);
		start = start->nextList;
	}
//	while ((*zik)->cmd)
//	{
		wait(NULL);
//		(*zik)->cmd = (*zik)->cmd->nextList;
//	}
	return (0);
}