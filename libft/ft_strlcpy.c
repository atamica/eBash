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

	l = 0;
	if (dst)
	{
		while (src && size-- && *src)
		{
			*dst++ = *src++;
			l++;
		}
		*dst = 0;
	}
	return (l);
}
