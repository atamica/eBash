/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:42:41 by atamica           #+#    #+#             */
/*   Updated: 2021/11/07 12:42:47 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	s_redir(char *ptr, char c, int *r, int code_redir)
{
	if ((*r != -1) && ptr && *ptr && (ptr[1] != c))
	{
		if (get_pos_char(ptr + 1, c))
			*r = ERROR;
		else
			*r |= code_redir;
	}
}

static void	d_redir(char *ptr, char c, int *r, int code_redir)
{
	if ((*r != -1) && ptr && *ptr && (ptr[1] == c))
	{
		if (get_pos_char(ptr + 2, c))
			*r = ERROR;
		else
			*r |= code_redir;
	}
}

int	find_redir(char *str)
{
	char	*tmp;
	int		res;

	res = NONE;
	if (str)
	{
		tmp = get_pos_char(str, L);
		s_redir(tmp, L, &res, S_LEFT);
		d_redir(tmp, L, &res, D_LEFT);
		tmp = get_pos_char(str, R);
		s_redir(tmp, R, &res, S_RIGHT);
		d_redir(tmp, R, &res, D_RIGHT);
	}
	return (res);
}

char	*filename(char *ptr)
{
	char	*st;

	if (!ptr)
		return (NULL);
	ptr = skip_spa(ptr);
	st = ptr;
	while (*ptr && !ft_isalsp(*ptr))
		ptr++;
	return (ft_substr(st, 0, ptr - st));
}
