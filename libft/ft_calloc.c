/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:58:23 by atamica           #+#    #+#             */
/*   Updated: 2020/11/07 19:22:01 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	tmp;
	void	*r;

	tmp = nmemb * size;
	r = (void *)malloc(tmp);
	if (r)
	{
		ft_bzero(r, tmp);
		return (r);
	}
	return (NULL);
}
