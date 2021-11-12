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

void	pid_children(char **envp, t_gnrl **zik, t_cmnd *start)
{
	while (start->nextList)
	{
		close(start->fd[0]);
		close(start->fd[1]);
		start = start->nextList;
	}
	pars_envp(envp, (*zik)->cmd->command_array, 0, 0);
}
