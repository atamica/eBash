/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:37:16 by atamica           #+#    #+#             */
/*   Updated: 2020/11/06 15:06:10 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	kw(char const *s, char c)
{
	size_t	r;
	size_t	i;
	size_t	l;

	r = 0;
	i = 0;
	while (s[i])
	{
		l = 0;
		while (s[i] && (s[i] != c))
		{
			l++;
			i++;
		}
		if (l)
			r++;
		if (s[i])
			i++;
	}
	return (r);
}

static size_t	lw(char const *s, char c, size_t *n)
{
	size_t	i;
	size_t	l;
	char	f;

	i = 0;
	*n = 0;
	while (s[i])
	{
		l = 0;
		f = 1;
		while (s[i] && (s[i] != c))
		{
			if (f)
			{
				*n = i;
				f = 0;
			}
			l++;
			i++;
		}
		if (l)
			return (l);
		i++;
	}
	return (0);
}

static char	**mlc(char **rt, char const *s, size_t wc, char c)
{
	size_t	i;
	size_t	l;
	size_t	n;

	rt[wc] = NULL;
	i = -1;
	while (wc--)
	{
		l = lw(s, c, &n);
		rt[++i] = (char *)malloc((l + 1) * sizeof(char));
		if (rt[i])
		{
			s += n;
			ft_strlcpy(rt[i], s, l + 1);
			s += l;
		}
		else
		{
			while (i)
				free(rt[--i]);
			free(rt);
			return (NULL);
		}
	}
	return (rt);
}

char	**ft_split(char const *s, char c)
{
	size_t	wc;
	char	**rt;

	if (s)
	{
		wc = kw(s, c);
		rt = (char **)malloc((wc + 1) * (sizeof(char *)));
		if (rt)
			return (mlc(rt, s, wc, c));
	}
	return (NULL);
}
