/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshavonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 19:40:45 by sshavonn          #+#    #+#             */
/*   Updated: 2020/12/13 16:43:06 by sshavonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

char	*put_nullterm_if_empty(char **s1, char **s2)
{
	char	*strjoin;

	strjoin = NULL;
	if (!(*s1) || !(*s2))
	{
		strjoin = malloc(sizeof(char) * 1);
		if (strjoin)
		{
			free(*s1);
			free(*s2);
			strjoin[0] = '\0';
		}
	}
	return (strjoin);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	join_len;
	char	*strjoin;

	strjoin = put_nullterm_if_empty(&s1, &s2);
	if (strjoin)
		return (strjoin);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join_len = s1_len + s2_len;
	strjoin = malloc((join_len + 1) * sizeof(char));
	if (strjoin)
	{
		ft_strlcpy(strjoin, s1, s1_len + 1);
		ft_strlcat(strjoin, s2, join_len + 1);
	}
	free(s1);
	free(s2);
	return (strjoin);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;

	if ((!dst) || (!src))
		return (0);
	n = ft_strlen(src);
	if (!dstsize)
		return (n);
	i = 0;
	while ((i != dstsize - 1) && (src[i] != '\0'))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (n);
}

int	ft_sizeof_line(char *buf)
{
	int	i;

	i = 0;
	while ((buf[i] != '\n') && buf[i] && i < BUFFER_SIZE)
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	slen;
	char	*pdup;

	pdup = NULL;
	slen = ft_strlen(s1);
	pdup = malloc(slen * sizeof(char) + 1);
	if (pdup)
		ft_strlcpy(pdup, s1, slen + 1);
	return (pdup);
}
