/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshavonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:29:22 by sshavonn          #+#    #+#             */
/*   Updated: 2020/12/17 22:34:47 by sshavonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <strings.h>
//# include <libgen.h>
# define BUFFER_SIZE 20

/* size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy (char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s1); */
char	*ft_strjoin_free(char *s1, char *s2);
int		get_next_line(int fd, char **line);

#endif
