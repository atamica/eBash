/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshavonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:59:31 by sshavonn          #+#    #+#             */
/*   Updated: 2020/12/20 17:59:38 by sshavonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	size_t	slen;
	char	*pdup;

	pdup = NULL;
	slen = ft_strlen(s1) + 1;
	if ((pdup = malloc(slen * sizeof(char))))
		ft_strlcpy(pdup, s1, slen);
	return (pdup);
}

int		ft_sizeof_line(char *buf)
{
	int i;

	i = 0;
	while ((buf[i] != '\n') && buf[i] && i < BUFFER_SIZE)
		i++;
	return (i);
}

int		ft_getline(char **line, char **line1, int fd)
{
	int		size;
	char	*line2;

	if (((size = ft_sizeof_line(*line1)) < BUFFER_SIZE) && (*line1)[size])
	{
		if ((*line = ft_substr(*line1, 0, size)))
		{
			ft_strlcpy(*line1, *line1 + size + 1, BUFFER_SIZE - size);
			return (1);
		}
		free(*line1);
		*line1 = NULL;
		return (-1);
	}
	if ((*line = ft_strdup(*line1)))
	{
		(*line1)[0] = '\0';
		if (((size = get_next_line(fd, &line2)) != -1))
			return (((*line = ft_strjoin_free(*line, line2))) ? size : -1);
	}
	free(*line1);
	*line1 = NULL;
	return (-1);
}

int		ft_fillbuff(char **line, char **line1, int fd)
{
	int size;

	size = 1;
	if (!(*line1)[0])
	{
		if ((size = read(fd, *line1, BUFFER_SIZE)) < 0)
		{
			free(*line1);
			*line1 = NULL;
			return (-1);
		}
		if (!size)
		{
			if (!(*line = malloc(1 * sizeof(char))))
				return (-1);
			(*line)[0] = '\0';
			return (0);
		}
		(*line1)[size] = '\0';
	}
	return (size);
}

int		get_next_line(int fd, char **line)
{
	static char	*line1;
	int			size;

	if (!line || BUFFER_SIZE < 1 || fd < 0)
		return (-1);
	*line = NULL;
	if (!(line1))
	{
		if (!(line1 = malloc((BUFFER_SIZE + 1) * sizeof(char))))
			return (-1);
		line1[0] = '\0';
	}
	if ((size = ft_fillbuff(line, &line1, fd)) < 0)
		return (-1);
	if (!size)
	{
		free(line1);
		line1 = NULL;
		return (0);
	}
	return (ft_getline(line, &line1, fd));
}
