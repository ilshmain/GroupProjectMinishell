#include "../../include/minishell.h"

void	add_export(t_list **ptr, char *str)
{
	t_list	*tmp;

	tmp = ft_lstnew(str);
	ft_lstadd_back(ptr, tmp);
}

void	ft_lstdel(t_list *lst)
{
	if (lst)
		free(lst->str);
	free(lst);
	lst = NULL;
}
