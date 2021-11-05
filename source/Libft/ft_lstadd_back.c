#include "libft.h"


void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ending;

	if (!lst)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{	
		ending = ft_lstlast(*lst);
		ending->next = new;
	}
}
