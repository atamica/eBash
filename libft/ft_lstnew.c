#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*r;

	r = (t_list *)malloc(sizeof(t_list));
	if (r)
	{
		r->content = content;
		r->next = NULL;
	}
	return (r);
}
