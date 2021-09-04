/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:08:37 by atamica           #+#    #+#             */
/*   Updated: 2020/11/08 10:00:14 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*d;
	unsigned char	cc;

	if (s)
	{
		d = (char *)s;
		cc = (unsigned char)c;
		while (*d)
		{
			if (*d == cc)
				return (d);
			d++;
		}
		if (!c)
			return (d);
	}
	return (NULL);
}
