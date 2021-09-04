/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:23:31 by atamica           #+#    #+#             */
/*   Updated: 2020/11/10 14:06:07 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			l;
	unsigned char	cc;

	if (s)
	{
		l = ft_strlen(s);
		if (!c)
			return ((char *)s + l);
		cc = (unsigned char)c;
		while (l)
		{
			if (s[l - 1] == cc)
				return ((char *)(s + l - 1));
			l--;
		}
	}
	return (NULL);
}
