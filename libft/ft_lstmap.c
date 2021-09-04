/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:10:30 by atamica           #+#    #+#             */
/*   Updated: 2020/11/09 13:14:19 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*result;

	result = NULL;
	if (!f || !del)
		return (NULL);
	while (lst)
	{
		newlist = ft_lstnew(f(lst->content));
		ft_lstadd_back(&result, newlist);
		if (!(newlist))
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (result);
}
