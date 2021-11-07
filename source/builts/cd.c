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

void	cdBuilt(t_list *ptr, t_gnrl *zik)
{
	int		i;
	char	*wayToChange;
	char	*wayAfterChange;

	i = 0;
	while (zik->cmd->command_array[i])
		i++;
	wayToChange = getcwd(NULL, 1000);
	if (i == 1)
		chdir(useWay(ptr, "HOME="));
	else if (ft_strcmp(zik->cmd->command_array[1], "-") == 0)
		chdir(useWay(ptr, "OLDPWD="));
	else
		chdir(zik->cmd->command_array[1]);
	wayAfterChange = getcwd(NULL, 1000);
	while (ptr)
	{
		if (ft_strncmp(ptr->str, "PWD", 3) == 0)
			ptr->str = ft_strjoin("PWD=", wayAfterChange);
		if (ft_strncmp(ptr->str, "OLDPWD=", 7) == 0)
			ptr->str = ft_strjoin("OLDPWD=", wayToChange);
		ptr = ptr->next;
	}
}
//**************************************