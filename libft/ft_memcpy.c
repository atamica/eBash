/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:19:15 by atamica           #+#    #+#             */
/*   Updated: 2020/10/31 19:19:53 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest)
	{
		i = 0;
		if (src)
		{
			while (n--)
			{
				*(char *)(dest + i) = *(char *)(src + i);
				i++;
			}
		}
	}
	return (dest);
}