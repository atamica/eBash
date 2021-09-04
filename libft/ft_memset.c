/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:12:55 by atamica           #+#    #+#             */
/*   Updated: 2020/11/17 17:17:12 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*b1;
	unsigned char	cc;

	b1 = b;
	cc = (unsigned char)c;
	while (len--)
		*b1++ = cc;
	return (b);
}
