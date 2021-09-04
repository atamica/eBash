/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:28:43 by atamica           #+#    #+#             */
/*   Updated: 2020/11/10 13:35:32 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	z;
	int	r;

	z = 1;
	r = 0;
	while (ft_isalsp(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			z = -1;
	while (ft_isdigit(*str))
	{
		if (r * 10 < r)
		{
			if (z < 0)
				return (0);
			return (-1);
		}
		r *= 10;
		r += *str++ - '0';
	}
	return (z * r);
}
