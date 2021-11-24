#include "../../include/minishell.h"

char *name(char **env)
{
	char	*str;
	int 	i;

	i = 0;

	str = NULL;
	while (env[i])
	{
		if (ft_strncmp("_=/Users", env[i], 8) == 0)
		{
			str = ft_strdup(change_ft_strrchr(env[i], '='));
			return (str);
		}
		i++;
	}
	return (str);
}

void	pars_envp(char **envp, char	**first_argv, int i, int k)
{
	char	**out;
	char	*search_PATH;
	char 	*path;
	char 	*new_out;

	while (envp[i])
	{
		if (ft_strcmp("./minishell", first_argv[0]) == 0)
		{
			path = name(envp);
			execve(path, first_argv, envp);
			free(path);
			ft_putstr_fd("Not executable file", STDERR_FILENO);
		}
		search_PATH = ft_strnstr(envp[i], "PATH=", 5);
		if (search_PATH)
		{
			search_PATH = ft_strrchr(search_PATH, '=');
			out = ft_split(search_PATH, ':');
			while (out[k])
			{
				i = 0;
				new_out = ft_strjoin(out[k], "/");
				out[k] = ft_strjoin(new_out, first_argv[0]);
				free(new_out);
				execve(out[k], first_argv, envp);
				free(out[k]);
				k++;
			}
			ft_putstr_fd("minishell$: ", STDERR_FILENO);
			ft_putstr_fd(first_argv[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			exit (127);
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
