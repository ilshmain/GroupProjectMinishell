#include "../../include/minishell.h"

int size_heredoc(char **argv)
{
	int i;
	i = 0;

	while (argv[i])
		i++;
	return (i - 1);
}

void Heredoc(char **argv, t_cmnd *cmd)
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
			write(1, "> ", 2);
			if (get_next_line(0, &buf) && ft_strncmp(buf, argv[i], ft_strlen(argv[i])))
			{
				if (len == i)
				{
					write(cmd->out, buf, ft_strlen(buf));
					write(cmd->out, "\n", 1);
				}
			}
			free(buf);
		}
		i++;
	}
	exit (0);
}

void	CheckHeredoc(char **argv, t_cmnd *cmd)
{
	int	fd[2];
	int pid;

	if (pipe(fd) < 0)
		ft_perror("Error pipe");
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		cmd->out = fd[1];
		Heredoc(argv, cmd);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		cmd->in = fd[0];
	}
}

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
