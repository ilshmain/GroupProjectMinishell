#include "../../include/minishell.h"

//ENV BUILT


char	*levelUpDown(char *str, int flag_up_down)
{
	char	*lvl;
	char	*buf;
	int		i;

	lvl = NULL;
	buf = change_ft_strrchr(str, '=');
	i = ft_atoi(buf);
	if (flag_up_down == 1)
		i++;
	else
		i--;
	lvl = ft_strjoin("SHLVL=", ft_itoa(i));
	return (lvl);
}

int	printEnvBuilt(t_list *ptr)
{
	while (ptr)
	{
		if (ft_strcmp("OLDPWD=", ptr->str) != 0)
			printf("%s\n", ptr->str);
		ptr = ptr->next;
	}
	return (1);
}

int	initialEnv(char **envp, t_list **ptr, int i)
{
	t_list	*tmp;

	*ptr = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD", 6) == 0)
			envp[i] = "OLDPWD=";
		if (ft_strncmp("SHLVL=", envp[i], 6) == 0)
			envp[i] = levelUpDown(envp[i], 1);
		tmp = ft_lstnew(envp[i]);
		ft_lstadd_back(ptr, tmp);
		i++;
	}
	return (1);
}
//**************************************