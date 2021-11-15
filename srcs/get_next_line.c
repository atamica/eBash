/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshavonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:30:31 by sshavonn          #+#    #+#             */
/*   Updated: 2020/12/19 20:18:30 by sshavonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

int	ft_strlcpy_if_eof(char **line, char **line1, int size)
{
	if ((size < BUFFER_SIZE) && (*line1)[size])
	{
		*line = ft_substr(*line1, 0, size);
		if (*line)
		{
			ft_strlcpy(*line1, *line1 + size + 1, BUFFER_SIZE - size);
			return (1);
		}
		free(*line1);
		*line1 = NULL;
		return (-1);
	}
	return (0);
}

int	ft_join_to_line(char **line1, char **line2, char **line, int fd)
{
	int	size;

	(*line1)[0] = '\0';
	size = get_next_line(fd, line2);
	if (size != -1)
	{
		*line = ft_strjoin_free(*line, *line2);
		if (*line)
			return (size);
		return (-1);
	}
	return (-1);
}

int	ft_getline(char **line, char **line1, int fd)
{
	int		size;
	char	*line2;
	int		f_res;

	size = ft_sizeof_line(*line1);
	f_res = ft_strlcpy_if_eof(line, line1, size);
	if (f_res)
		return (f_res);
	*line = ft_strdup(*line1);
	if (*line)
	{	
		size = ft_join_to_line(line1, &line2, line, fd);
		if (size != -1)
			return (size);
	}
	free(*line1);
	*line1 = NULL;
	return (-1);
}

int	ft_fillbuff(char **line, char **line1, int fd)
{
	int	size;

	size = 1;
	if (!(*line1)[0])
	{
		size = read(fd, *line1, BUFFER_SIZE);
		if (size < 0)
		{
			free(*line1);
			*line1 = NULL;
			return (-1);
		}
		if (!size)
		{
			*line = malloc(1 * sizeof(char));
			if (!(*line))
				return (-1);
			(*line)[0] = '\0';
			return (0);
		}
		(*line1)[size] = '\0';
	}
	return (size);
}

int	get_next_line(int fd, char **line)
{
	static char	*line1;
	int			size;

	*line = NULL;
	if (!line || BUFFER_SIZE < 1 || fd < 0)
		return (-1);
	if (!(line1))
	{
		line1 = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!(line1))
			return (-1);
		line1[0] = '\0';
	}
	size = ft_fillbuff(line, &line1, fd);
	if (size < 0)
		return (-1);
	if (!size)
	{
		free(line1);
		line1 = NULL;
		return (0);
	}
	return (ft_getline(line, &line1, fd));
}
