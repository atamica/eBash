/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:22:05 by atamica           #+#    #+#             */
/*   Updated: 2020/10/31 19:34:01 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	cmp;

	while (n--)
	{
		cmp = *((unsigned char *)(s1++)) - *((unsigned char *)(s2++));
		if (cmp)
			return (cmp);
	}
	return (0);
}
