#include "../../include/minishell.h"

// cd BUILT*****************************
char	*useWay(t_list *ptr, char *comand)
{
	int		i;
	char	*NewWay;

	NewWay = NULL;
	i = (int)ft_strlen(comand);
	while (ptr)
	{
		if ((ft_strncmp(ptr->str, comand, i) == 0))
		{
			NewWay = change_ft_strrchr(ptr->str, '=');
			break ;
		}
		ptr = ptr->next;
	}
	return (NewWay);
}

void change_str_value(t_list *ptr, char *wayAfterChange, char *wayToChange)
{
	while (ptr)
	{
		if (ft_strncmp(ptr->str, "PWD", 3) == 0)
		{
			free(ptr->str);
			ptr->str = ft_strjoin("PWD=", wayAfterChange);
		}
		if (ft_strncmp(ptr->str, "OLDPWD=", 7) == 0)
		{
			free(ptr->str);
			ptr->str = ft_strjoin("OLDPWD=", wayToChange);
		}
		ptr = ptr->next;
	}
}

void Oldpwd_Way(t_list *ptr)
{
	exit_code = chdir(useWay(ptr, "OLDPWD="));
	if (exit_code == -1)
	{
		exit_code = 1;
		ft_putstr_fd("minishell$ cd: OLDPWD not set\n", STDERR_FILENO);
	}
}

void Other_Way(t_gnrl *zik)
{
	exit_code = 1;
	ft_putstr_fd("minishell$ cd: ", STDERR_FILENO);
	ft_putstr_fd(zik->cmd->command_array[1], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

int	cdBuilt(t_list *ptr, t_gnrl *zik)
{
	int		i;
	char	*wayToChange;
	char	*wayAfterChange;

	i = 0;
	while (zik->cmd->command_array[i])
		i++;
	wayToChange = getcwd(NULL, 1024);
	if (wayToChange == NULL)
		wayToChange = useWay(ptr, "PWD=");
	if (i == 1)
		exit_code = chdir(useWay(ptr, "HOME="));
	else if (ft_strcmp(zik->cmd->command_array[1], "-") == 0)
		Oldpwd_Way(ptr);
	else
		exit_code = chdir(zik->cmd->command_array[1]);
	if (exit_code == -1)
	{
		Other_Way(zik);
		return (1);
	}
	else
		exit_code = 0;
	wayAfterChange = getcwd(NULL, 1024);
	change_str_value(ptr, wayAfterChange, wayToChange);
	free(wayToChange);
	free(wayAfterChange);
	return (1);
}
//**************************************