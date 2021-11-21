#include "../../include/minishell.h"

// Export Built
int 	dopSortirovka(t_list **list)
{
	char	*str;
	t_list	*tmp;
	t_list	*lst;
	int		flag;

	flag = 1;
	lst = *list;
	while ((lst->next != NULL) && (lst->next))
	{
		tmp = ft_lstnew((lst->next)->str);
		if (ft_strcmp(lst->str, tmp->str) > 0)
		{
			str = malloc(sizeof (char *));
			if (!str)
				return 0;
			str = lst->str;
			lst->str = tmp->str;
			(lst->next)->str = str;
			flag--;
		}
		lst = lst->next;
	}
	return (flag);
}

void	sortAlphabet(t_list **sortMas)
{
	t_list *lst;
	int 	flag;

	while (1)
	{
		lst = *sortMas;
		flag = dopSortirovka(&lst);
		lst = lst->next;
		if (flag == 1)
			break;
	}
}

void	printExport(t_list *ptr, t_list **sortMas)
{
	t_list *tmp;

	*sortMas = NULL;
	while(ptr)
	{
		tmp = ft_lstnew(ptr->str);
		ft_lstadd_back(sortMas, tmp);
		ptr = ptr->next;
	}
	sortAlphabet(sortMas);
	while (*sortMas)
	{
		if (ft_strncmp("_=", (*sortMas)->str, 2) != 0)
		{
			if (ft_strcmp("OLDPWD=", (*sortMas)->str) == 0)
				printf("declare -x OLDPWD\n");
			else
				printf("declare -x %s\n", (*sortMas)->str);
		}

		*sortMas = (*sortMas)->next;
	}
}

void	addExport(t_list **ptr, char *str)
{
	t_list	*tmp;
	tmp = ft_lstnew(str);
	ft_lstadd_back(ptr, tmp);
}

int checking_validity_string(char *str)
{
	int i;

	i = 0;

	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exportBuilt(t_list *ptr, t_gnrl *zik)
{
	int		i;
	t_list	*sortMas;
	char	*print_error;

	i = 0;
	exit_code = 0;
	while (zik->cmd->command_array[i])
		i++;
	if (i == 1)
		printExport(ptr, &sortMas);
	else
	{
		i = 1;
		while (zik->cmd->command_array[i])
		{
			if (checking_validity_string(zik->cmd->command_array[i]) == 1)
			{
				exit_code = 1;
				print_error = ft_strjoin("export: ", zik->cmd->command_array[i]);
				ft_putstr_fd(print_error, STDOUT_FILENO);
				ft_putstr_fd(": not a valid identifier", STDOUT_FILENO);
				ft_putstr_fd("\n", STDOUT_FILENO);
				free(print_error);
				print_error = NULL;
			}
			if (ft_strchr(zik->cmd->command_array[i], '=') != 0)
				addExport(&ptr, zik->cmd->command_array[i]);
			i++;
		}
	}
	return (1);
}
//**************************************