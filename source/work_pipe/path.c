/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmint <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:20:15 by fmint             #+#    #+#             */
/*   Updated: 2021/11/29 12:20:33 by fmint            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*name(char **env)
{
	char	*str;
	int		i;

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

void	shell_name(char **envp, char **first_argv)
{
	char	*path;

	path = name(envp);
	execve(path, first_argv, envp);
	free(path);
	ft_putstr_fd("Not executable file", STDERR_FILENO);
}

char	**dop_path(char *search_path, char **out, char *str)
{
	int		i;
	char	*new_out;

	i = 0;
	if (search_path == 0)
	{
		ft_putstr_fd("minishell$: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		g_exit_code = 127;
		exit(g_exit_code);
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

char	**path(char **envp, int i, char *str)
{
	char	**out;
	char	*search_path;

	out = NULL;
	while (envp[i])
	{
		search_path = ft_strnstr(envp[i], "PATH=", 5);
		if (search_path)
		{
			search_path = ft_strrchr(search_path, '=');
			out = ft_split(search_path, ':');
			break ;
		}
		i++;
	}
	return (dop_path(search_path, out, str));
}

void	pars_envp(char **envp, char	**first_argv, int i, int k)
{
	char	*out;
	char	**new_out;

	if (ft_strcmp("./minishell", first_argv[0]) == 0)
		shell_name(envp, first_argv);
	new_out = path(envp, i, first_argv[0]);
	while (new_out[k])
	{
		out = ft_strjoin(new_out[k], first_argv[0]);
		free(new_out[k]);
		execve(out, first_argv, envp);
		free(out);
		k++;
	}
	free(new_out);
	if (ft_strchr(first_argv[0], '/'))
		print_error(first_argv[0], ": No such file or directory\n");
	else
		print_error(first_argv[0], ": command not found\n");
	exit (127);
}
