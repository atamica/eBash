#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new && lst)
	{
		if (*lst)
		{
			new->next = *lst;
			*lst = new;
		}
		else
		{
			*lst = new;
			(*lst)->next = NULL;
		}
	}
}
