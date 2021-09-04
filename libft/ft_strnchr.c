/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:20:16 by atamica           #+#    #+#             */
/*   Updated: 2020/11/03 01:49:24 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strnchr(const char *s, int c, size_t n)
{
	char	*r;
	char	cc;

	r = (void *)(0);
	cc = (unsigned char)c;
	while ((n--) && (*s))
	{
		if (*s == cc)
			r = (char *)s;
		s++;
	}
	return (r);
}
