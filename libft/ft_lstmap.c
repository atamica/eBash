#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*result;

	result = NULL;
	if (!f)
		return (NULL);
	while (lst)
	{
		newlist = ft_lstnew(f(lst->content));
		ft_lstadd_back(&result, newlist);
		if (!(newlist))
		{
			if (del)
				ft_lstclear(&result, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (result);
}
