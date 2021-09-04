/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:07:12 by atamica           #+#    #+#             */
/*   Updated: 2020/11/09 10:22:28 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
