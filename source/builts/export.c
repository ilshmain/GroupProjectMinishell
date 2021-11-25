#include "../../include/minishell.h"

// Export Built
int	dop_sortirovka(t_list **list)
{
	char	*str;
	char	*tmp;
	t_list	*lst;
	int		flag;

	flag = 1;
	lst = *list;
	while ((lst->next != NULL) && (lst->next))
	{
		if (ft_strcmp(lst->str, (lst->next)->str) > 0)
		{
			tmp = ft_strdup((lst->next)->str);
			str = ft_strdup(lst->str);
			free(lst->str);
			free((lst->next)->str);
			lst->str = ft_strdup(tmp);
			(lst->next)->str = ft_strdup(str);
			free(str);
			free(tmp);
			flag--;
		}
		lst = lst->next;
	}
	return (flag);
}

void	sort_alphabet(t_list **sortMas)
{
	t_list	*lst;
	int		flag;

	while (1)
	{
		lst = *sortMas;
		flag = dop_sortirovka(&lst);
		if (flag == 1)
			break ;
	}
}

void	print_sortmas(t_list **sortMas)
{
	t_list	*new;

	while (*sortMas)
	{
		new = (*sortMas)->next;
		if (ft_strncmp("_=", (*sortMas)->str, 2) != 0)
		{
			if (ft_strcmp("OLDPWD=", (*sortMas)->str) == 0)
				printf("declare -x OLDPWD\n");
			else
				printf("declare -x %s\n", (*sortMas)->str);
		}
		ft_lstdel(*sortMas);
		*sortMas = new;
	}
}

void	print_export(t_list *ptr, t_list **sortMas)
{
	t_list	*tmp;
	char	*dop_str;

	*sortMas = NULL;
	while (ptr)
	{
		dop_str = ft_strdup(ptr->str);
		tmp = ft_lstnew(dop_str);
		ft_lstadd_back(sortMas, tmp);
		ptr = ptr->next;
	}
	sort_alphabet(sortMas);
	print_sortmas(&(*sortMas));
}

int	export_built(t_list *ptr, t_gnrl *zik)
{
	int		i;
	t_list	*sort_mas;

	i = 0;
	exit_code = 0;
	while (zik->cmd->command_array[i])
		i++;
	if (i == 1)
		print_export(ptr, &sort_mas);
	else
	{
		i = 1;
		while (zik->cmd->command_array[i])
		{
			if (checking_validity_string(zik->cmd->command_array[i]) == 1)
			{
				print_error_func("minishell$: export: ", \
					zik->cmd->command_array[i]);
			}
			if (ft_strchr(zik->cmd->command_array[i], '=') != 0)
				add_export(&ptr, zik->cmd->command_array[i]);
			i++;
		}
	}
	return (1);
}
//**************************************