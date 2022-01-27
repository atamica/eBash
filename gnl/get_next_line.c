/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:47:09 by atamica           #+#    #+#             */
/*   Updated: 2020/11/24 22:52:47 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	findn(const char *s)
{
	int				i;

	i = -1;
	if (s)
	{
		while (s[++i])
			if (s[i] == C)
				return (i);
	}
	return (-1);
}

static int	fre(int result, char **buf, char **remain, char **line)
{
	if (buf && *buf)
	{
		free(*buf);
		*buf = NULL;
	}
	if (remain && *remain)
	{
		free(*remain);
		*remain = NULL;
	}
	if (line && *line)
	{
/* 		free(*line);
		*line = NULL;*/
	} 
	return (result);
}

static int	divider(char *src, char **line, char **remain, int cc)
{
	int			i;
	char		*tmp;

	if ((i = findn(src)) > -1)
	{
		tmp = ft_substr(src, 0, i);
		*line = ft_strjoin_mod(line, tmp);
		fre(1, &tmp, NULL, NULL);
		tmp = *remain;
		*remain = ft_substr(src, i + 1, cc - i);
		return (fre(1, &tmp, NULL, NULL));
	}
	*line = ft_strjoin_mod(line, src);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char *remain = NULL;
	ssize_t		count_char;
	char		*buf;

	if ((fd >= 0) && (BUFFER_SIZE > 0) && (BUFFER_SIZE <= MAX_BUF_SIZE) &&\
line && (buf = (char*)malloc(BUFFER_SIZE + 1)) && (read(fd, buf, 0) != -1))
	{
		*line = ft_substr("", 0, 0);
		if (remain && divider(remain, line, &remain, ft_strlen(remain)))
			return (fre(1, &buf, NULL, NULL));
		while (((count_char = read(fd, buf, BUFFER_SIZE)) > 0))
		{
			buf[count_char] = 0;
			if (divider(buf, line, &remain, count_char))
				return (fre(1, &buf, NULL, NULL));
		}
		if (count_char == 0)
			return (fre(0, &buf, &remain, NULL));
	}
	return (fre(-1, &buf, &remain, line));
}
