/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:14:32 by atamica           #+#    #+#             */
/*   Updated: 2020/11/08 09:57:02 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		c0;
	char		*d;
	char const	*s;

	if (dst && src && n)
	{
		c0 = (unsigned char)c;
		d = (char *)dst;
		s = (char *)src;
		while (n--)
		{
			*d = *s;
			if (c0 == *s)
				return (++d);
			d++;
			s++;
		}
	}
	return (NULL);
}
