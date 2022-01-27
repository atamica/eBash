/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 23:00:14 by atamica           #+#    #+#             */
/*   Updated: 2020/11/24 23:00:58 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# define C '\n'
# define MAX_BUF_SIZE 10000000
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

/*
**	function which returns a line read from a file descriptor (fd),
**	without the newline.
**	Return value:
**	1 : A line has been read
**	0 : EOF has been reached
**	-1 : An error happened
*/

int		get_next_line(int fd, char **line);

/*
**	function which returns duplicate s if del != 0
**	and free *s
*/

char	*ft_strdup_mod(char **s, int del);

/*
**	function which returns s1 + s2
**	and free *s1
*/

# ifndef LIBFT_H

/*
**	function which returns size of s
*/

size_t	ft_strlen(const char *s);

/*
**	function which copy src in dst
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/*
**	function which returns part of s
*/

char	*ft_substr(char const *s, unsigned int start, size_t len);

# endif

char	*ft_strjoin_mod(char **s1, char *s2);

#endif
