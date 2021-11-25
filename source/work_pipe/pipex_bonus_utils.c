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

void shell_name(char **envp, char **first_argv)
{
	char 	*path;

	path = name(envp);
	execve(path, first_argv, envp);
	free(path);
	ft_putstr_fd("Not executable file", STDERR_FILENO);
}

char **Path(char **envp, int i)
{
	char 	**out;
	char	*search_PATH;
	char 	*new_out;

	out = NULL;
	while (envp[i])
	{
		search_PATH = ft_strnstr(envp[i], "PATH=", 5);
		if (search_PATH)
		{
			search_PATH = ft_strrchr(search_PATH, '=');
			out = ft_split(search_PATH, ':');
			i = 0;
			break;
		}
		i++;
	}
	while (out[i])
	{
		new_out = ft_strjoin(out[i], "/");
		free(out[i]);
		out[i] = ft_strdup(new_out);
		free(new_out);
		i++;
	}
	return (out);
}

void	pars_envp(char **envp, char	**first_argv, int i, int k)
{
	char	*out;
	char 	**new_out;

	if (ft_strcmp("./minishell", first_argv[0]) == 0)
		shell_name(envp, first_argv);
	new_out = Path(envp, i);
	while(new_out[k])
	{
		out = ft_strjoin(new_out[k], first_argv[0]);
		free(new_out[k]);
		execve(out, first_argv, envp);
		free(out);
		k++;
	}
	free(new_out);
	ft_putstr_fd("minishell$: ", STDERR_FILENO);
	ft_putstr_fd(first_argv[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit (127);
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
	char 	**new_env;

	new_env = env((*zik)->ptr);
	while (start->nextList)
	{
		close(start->fd[0]);
		close(start->fd[1]);
		start = start->nextList;
	}
	if ((built_func((*zik), (*zik)->ptr) == 1) && ((*zik)->cmd->fork == 1))
		exit (0);
	pars_envp(new_env, (*zik)->cmd->command_array, 0, 0);
	return (1);
}

//int main(int argc, char **argv, char **envp) {
//	(void) argc;
//	(void) argv;
//	char **qwe;
//
//	qwe = ft_split("ls", ' ');
//	pars_envp(envp, qwe, 0, 0);
//	return (1);
//}