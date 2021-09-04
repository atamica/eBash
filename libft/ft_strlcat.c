/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:30:58 by atamica           #+#    #+#             */
/*   Updated: 2020/10/31 20:35:03 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	l;
	size_t	r;

	l = 0;
	while (dst[l])
		l++;
	if (size < l)
		r = size + ft_strlen(src);
	else
		r = l + ft_strlen(src);
	while ((size > l + 1) && *src)
		dst[l++] = *src++;
	dst[l] = '\0';
	return (r);
}
