/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshavonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:32:42 by sshavonn          #+#    #+#             */
/*   Updated: 2020/12/17 22:33:17 by sshavonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t dstlen;
	size_t srclen;
	size_t i;
	size_t j;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = dstlen;
	j = 0;
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	while ((j < dstsize - dstlen - 1) && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dstlen + srclen);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	minlen;
	size_t	slen;

	substr = NULL;
	if (!s)
		return (substr);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		if ((substr = malloc(sizeof(char))))
		{
			substr[0] = '\0';
			return (substr);
		}
		else
			return (NULL);
	}
	minlen = (len > (slen - start) ? slen - start : len);
	if ((substr = malloc(minlen * sizeof(char) + 1)))
	{
		ft_strlcpy(substr, (s + start), minlen + 1);
	}
	return (substr);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	join_len;
	char	*strjoin;

	strjoin = NULL;
	if (!s1 || !s2)
		if ((strjoin = malloc(sizeof(char) * 1)))
		{
			free(s1);
			free(s2);
			strjoin[0] = '\0';
			return (strjoin);
		}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join_len = s1_len + s2_len;
	if ((strjoin = malloc((join_len + 1) * sizeof(char))))
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
	size_t i;
	size_t n;

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
