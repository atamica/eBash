#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (new)
	{
		if (*lst)
		{
			tmp = *lst;
			ft_lstlast(tmp)->next = new;
			new->next = NULL;
		}
		else
		{
			*lst = new;
			(*lst)->next = NULL;
		}
	}
}
