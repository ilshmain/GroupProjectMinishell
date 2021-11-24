#include "../../include/minishell.h"

// cd BUILT*****************************
//char *cd_error()

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
			ft_putstr_fd(NewWay, 1);
			break ;
		}
		ptr = ptr->next;
	}
	return (NewWay);
}

int	cdBuilt(t_list *ptr, t_gnrl *zik)
{
	int		i;
	char	*wayToChange;
	char	*wayAfterChange;
	char	*print_error;

	i = 0;
	while (zik->cmd->command_array[i])
		i++;
	wayToChange = getcwd(NULL, 1000);
	if (wayToChange == NULL)
		wayToChange = useWay(ptr, "PWD=");
	if (i == 1)
		chdir(useWay(ptr, "HOME="));
	else if (ft_strcmp(zik->cmd->command_array[1], "-") == 0)
	{
		exit_code = chdir(useWay(ptr, "OLDPWD="));
		if (exit_code == -1)
		{
			exit_code = 1;
			ft_putstr_fd("cd: OLDPWD not set\n", STDOUT_FILENO);
		}
	}
	else
		exit_code = chdir(zik->cmd->command_array[1]);
	if (exit_code == -1)
	{
		exit_code = 1;
		print_error = ft_strjoin("cd: ", zik->cmd->command_array[1]);
		ft_perror_2(print_error);
	}
	else
		exit_code = 0;
	wayAfterChange = getcwd(NULL, 1000);
	while (ptr)
	{
		if (ft_strncmp(ptr->str, "PWD", 3) == 0)
			ptr->str = ft_strjoin("PWD=", wayAfterChange);
		if (ft_strncmp(ptr->str, "OLDPWD=", 7) == 0)
			ptr->str = ft_strjoin("OLDPWD=", wayToChange);
		ptr = ptr->next;
	}
	return (1);
}
//**************************************