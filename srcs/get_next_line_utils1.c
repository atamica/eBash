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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	size_t	j;

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

char	*allocate_nul_term(void)
{
	char	*substr;

	substr = NULL;
	substr = malloc(sizeof(char) * 1);
	if (substr)
		substr[0] = '\0';
	return (substr);
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
		return (allocate_nul_term());
	if (len > (slen - start))
		minlen = slen - start;
	else
		minlen = len;
	substr = malloc(minlen * sizeof(char) + 1);
	if (substr)
	{
		ft_strlcpy(substr, (s + start), minlen + 1);
	}
	return (substr);
}
