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
				execve(out[k], first_argv, envp);
				k++;
			}
			ft_perror("Wrong command");
		}
		i++;
	}
}

int len_lst(t_list *lst)
{
	int i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char **env(t_list *lst)
{
	char	**new_env;
	int		len;
	int		i;

	i = 0;
	len = len_lst(lst);
	new_env = malloc(sizeof(char **) * len);
	while (lst)
	{
		new_env[i] = lst->str;
		lst = lst->next;
		i++;
	}
	return (new_env);
}

int	pid_children(char **envp, t_gnrl **zik, t_cmnd *start)
{
	(void)envp;
	char **new_env;

	new_env = env((*zik)->ptr);
	while (start->nextList)
	{
		close(start->fd[0]);
		close(start->fd[1]);
		start = start->nextList;
	}
	if ((builtFunc((*zik), (*zik)->ptr) == 1) && ((*zik)->cmd->fork == 1))
		exit (0);
	pars_envp(new_env, (*zik)->cmd->command_array, 0, 0);
	return (1);
}
