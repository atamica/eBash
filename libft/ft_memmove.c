/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:28:37 by atamica           #+#    #+#             */
/*   Updated: 2020/11/08 09:58:35 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*d;
	char const	*s;

	if (dst && src)
	{
		d = (char *)(dst);
		s = (char *)(src);
		if (dst < src)
			while (n--)
				*d++ = *s++;
		if (src < dst)
			while (n--)
				d[n] = s[n];
	}
	return (dst);
}
