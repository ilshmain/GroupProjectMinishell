#include "../../include/minishell.h"

void	pars_envp(char **envp, char	**first_argv, int i, int k)
{
	char	**out;
	char	*search_PATH;

	while (envp[i])
	{
		search_PATH = ft_strnstr(envp[i], "PATH=", 5);
		if (search_PATH)
		{
			search_PATH = ft_strrchr(search_PATH, '=');
			out = ft_split(search_PATH, ':');
			while (out[k])
			{
				i = 0;
				out[k] = ft_strjoin(out[k], "/");
				out[k] = ft_strjoin(out[k], first_argv[0]);
				execve(out[k], first_argv, NULL);
				k++;
			}
			ft_perror("Wrong command");
		}
		i++;
	}
}

void	pid_parent(t_map *st, char **envp, t_gnrl **zik)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	dup2(st[st->i - 1].fd[0], 0);
	if (((*zik)->cmd->fd_write != 0) || ((*zik)->cmd->fd_reWrite != 0))
	{
		if (dup2(st->file2, 1) < 0)
			ft_perror("Errror open file2");
	}
	close(st[st->i - 1].fd[0]);
	close(st[st->i - 1].fd[1]);
	pars_envp(envp, (*zik)->cmd->command_array, i, k);
}

void	pid_children(t_map *st, char **envp, t_gnrl **zik)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (st->sum_lst != 1)
	{
		if (st->i != 0)
		{
			close(st[st->i - 1].fd[1]);
			if (dup2(st[st->i - 1].fd[0], 0) < 0)
				ft_perror("Error pid_children");
			close(st[st->i - 1].fd[0]);
		}
		if (st->i + 1 != st->sum_lst)
		{
			if (dup2(st[st->i].fd[1], 1) < 0)
				ft_perror("Error pid_children");
			close(st[st->i].fd[0]);
			close(st[st->i].fd[1]);
		}
	}
	pars_envp(envp, (*zik)->cmd->command_array, i, k);
}
