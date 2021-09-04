/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:04:30 by atamica           #+#    #+#             */
/*   Updated: 2020/11/09 09:55:18 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
