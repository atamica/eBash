/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:49:53 by atamica           #+#    #+#             */
/*   Updated: 2020/11/08 23:01:15 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	size_t	dl;
	size_t	db;

	if (big && lit)
	{
		dl = ft_strlen(lit);
		if (!dl)
			return ((char *)big);
		if (dl > len)
			return (NULL);
		db = ft_strlen(big);
		if (db >= dl)
		{
			db = len - dl + 1;
			while (*big && db--)
			{
				if (ft_memcmp(big, lit, dl))
					big++;
				else
					return ((char *)(big));
			}
		}
	}
	return (NULL);
}
