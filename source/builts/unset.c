#include "../../include/minishell.h"

// unset BUILT*****************************

void	unset_env(t_list *ptr, char *str)
{
	t_list	*tmp;

	while (ptr->next != NULL)
	{
		if (ft_strncmp(ptr->next->str, str, ft_strlen(str)) == 0)
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			free (tmp->str);
			free (tmp);
			break ;
		}
		ptr = ptr->next;
	}
}

int	unset_built(t_list *ptr, t_gnrl *zik)
{
	int		i;

	i = 0;
	exit_code = 0;
	while (zik->cmd->command_array[i])
		i++;
	if (i != 1)
	{
		i = 1;
		while (zik->cmd->command_array[i])
		{
			if (checking_validity_string(zik->cmd->command_array[i]) == 1)
				print_error_func("unset: ", zik->cmd->command_array[i]);
			if (ft_strchr(zik->cmd->command_array[i], '=') != 0)
				print_error_func("unset: ", zik->cmd->command_array[i]);
			unset_env(ptr, zik->cmd->command_array[i]);
			i++;
		}
	}
	return (1);
}

//*****************************************