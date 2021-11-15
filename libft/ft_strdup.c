/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:00:57 by atamica           #+#    #+#             */
/*   Updated: 2020/11/06 17:57:37 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*r;
	size_t	l;

	l = ft_strlen(s);
	r = (char *)malloc((l + 1) * sizeof(char));
	if (r)
		ft_strlcpy(r, s, l);
	return (r);
}
