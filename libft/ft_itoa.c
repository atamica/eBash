/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:38:08 by atamica           #+#    #+#             */
/*   Updated: 2020/11/08 10:49:04 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	tst(int n, int *z, unsigned int *l, unsigned int *m)
{
	unsigned int	r;

	*l = 1;
	*m = 1;
	if (n < 0)
	{
		r = -n;
		*z = 1;
	}
	else
	{
		r = n;
		*z = 0;
	}
	while ((n < -9) || (n > 9))
	{
		(*l)++;
		*m *= 10;
		n /= 10;
	}
	return (r);
}

char	*ft_itoa(int n)
{
	char			*s;
	int				z;
	unsigned int	m;
	unsigned int	l;
	unsigned int	tmp;

	tmp = tst(n, &z, &l, &m);
	s = malloc((l + 1 + z) * sizeof(char));
	if (s)
	{
		if (z)
			*s = '-';
		while (m)
		{
			l = tmp / m;
			*(s + z++) = '0' + l;
			tmp -= l * m;
			m /= 10;
		}
		*(s + z) = '\0';
	}
	return (s);
}
