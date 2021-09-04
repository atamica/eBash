/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:33:07 by atamica           #+#    #+#             */
/*   Updated: 2020/11/08 10:53:21 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	l1;
	size_t	l2;

	if (s1 && s2)
	{
		l1 = ft_strlen(s1);
		l2 = ft_strlen(s2);
		r = (char *)malloc((l1 + l2 + 1) * sizeof(char));
		if (r)
		{
			ft_strlcpy(r, s1, l1 + 1);
			ft_strlcpy(r + l1, s2, l2 + 1);
			return (r);
		}
	}
	return (NULL);
}
