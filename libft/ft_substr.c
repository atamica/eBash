/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:28:55 by atamica           #+#    #+#             */
/*   Updated: 2020/11/07 23:22:41 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	l;

	r = NULL;
	if (s)
	{
		l = ft_strlen(s);
		if (start > l)
			start = l;
		if (l < len + start)
			len = l - start;
		r = ft_calloc(len + 1, sizeof(char));
		if (r)
			ft_strlcpy(r, s + start, len);
	}
	return (r);
}
