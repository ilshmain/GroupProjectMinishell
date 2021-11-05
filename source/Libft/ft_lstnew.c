#include "libft.h"

t_list	*ft_lstnew(char *str)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	tmp->str = str;
	tmp->next = NULL;
	return (tmp);
}
