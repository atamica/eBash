/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:26:01 by atamica           #+#    #+#             */
/*   Updated: 2020/10/31 20:34:35 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	l;
	size_t	r;

	if (dst && src)
	{
		r = ft_strlen(src);
		if (size)
		{
			l = 0;
			while (*(src + l) && (size > (l + 1)))
			{
				*(dst + l) = *(src + l);
				l++;
			}
			dst[l] = '\0';
		}
		return (r);
	}
	return (0);
}
