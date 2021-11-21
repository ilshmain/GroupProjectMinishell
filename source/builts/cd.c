#include "../../include/minishell.h"

// cd BUILT*****************************
char	*useWay(t_list *ptr, char *comand)
{
	int		i;
	char	*NewWay;

	NewWay = NULL;
	i = ft_strlen(comand);
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

int	cdBuilt(t_list *ptr, t_gnrl *zik)
{
	int		i;
	char	*wayToChange;
	char	*wayAfterChange;

	i = 0;
	while (zik->cmd->command_array[i])
		i++;
	wayToChange = getcwd(NULL, 1000);
	if (wayToChange == NULL)
		wayToChange = useWay(ptr, "PWD=");
	if (i == 1)
		chdir(useWay(ptr, "HOME="));
	else if (ft_strcmp(zik->cmd->command_array[1], "-") == 0)
		chdir(useWay(ptr, "OLDPWD="));
	else
		exit_code = chdir(zik->cmd->command_array[1]);
	if (exit_code == -1)
		ft_perror("cd");
	else
		exit_code = 0;
	wayAfterChange = getcwd(NULL, 1000);
	while (ptr)
	{
		if (ft_strncmp(ptr->str, "PWD", 3) == 0)
			ptr->str = ft_strjoin("PWD=", wayAfterChange);
		if (ft_strncmp(ptr->str, "OLDPWD=", 7) == 0)
			ptr->str = ft_strjoin("OLDPWD=", wayToChange);
//		printf("wayAfterChange %s\n", wayAfterChange);
//		printf("wayToChange %s\n", wayToChange);
		ptr = ptr->next;
	}
	return (1);
}
//**************************************