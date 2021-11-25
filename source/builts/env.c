#include "../../include/minishell.h"

//ENV BUILT
char	*level_up_down(char *str)
{
	char	*lvl;
	char	*buf;
	char	*itoa_value;
	int		i;

	lvl = NULL;
	buf = change_ft_strrchr(str, '=');
	i = ft_atoi(buf);
	itoa_value = ft_itoa(++i);
	lvl = ft_strjoin("SHLVL=", itoa_value);
	free(itoa_value);
	return (lvl);
}

int	print_env_built(t_list *ptr)
{
	while (ptr)
	{
		if (ft_strcmp("OLDPWD=", ptr->str) != 0)
			printf("%s\n", ptr->str);
		ptr = ptr->next;
	}
	return (1);
}

int	initial_env(char **envp, t_list **ptr, int i)
{
	t_list	*tmp;
	char	*str;

	*ptr = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD", 6) == 0)
			str = ft_strdup("OLDPWD=");
		else if (ft_strncmp("SHLVL=", envp[i], 6) == 0)
			str = level_up_down(envp[i]);
		else
			str = ft_strdup(envp[i]);
		tmp = ft_lstnew(str);
		ft_lstadd_back(ptr, tmp);
		i++;
	}
	return (1);
}
//**************************************