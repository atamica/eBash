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

int	err_open(int fd, t_d *d)
{
	if (fd < 0)
	{
		err_msg(MSGE4, 0, d);
		return (ERROR);
	}
	return (SUCCSESS);
}

static void	s_redir(char *ptr, char c, int *r, int code_redir)
{
	if ((*r != -1) && ptr && *ptr && (ptr[1] != c))
	{
		if (ft_get_spec_ch(ptr + 1, c))
			*r = ERROR;
		else
			*r |= code_redir;
	}
}

static void	d_redir(char *ptr, char c, int *r, int code_redir)
{
	if ((*r != -1) && ptr && *ptr && (ptr[1] == c))
	{
		if (ft_get_spec_ch(ptr + 2, c))
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
		tmp = ft_get_spec_ch(str, L);
		s_redir(tmp, L, &res, S_LEFT);
		d_redir(tmp, L, &res, D_LEFT);
		tmp = ft_get_spec_ch(str, R);
		s_redir(tmp, R, &res, S_RIGHT);
		d_redir(tmp, R, &res, D_RIGHT);
	}
	return (res);
}

char	*filename(char *ptr)
{
	char	*st;
	char	*t;

	if (ptr)
	{
		while (*ptr && ft_isalsp(*ptr))
			ptr++;
		st = ptr;
		while (*ptr && !ft_isalsp(*ptr))
			ptr++;
		t = ft_substr(st, 0, ptr - st);
		return (t);
	}
	return (NULL);
}

/* 
t_rd	redir(char *str, t_cmd *cmd, t_d *d)
{
	t_rd	r;

	r = (t_rd){.code_in = cmd->redir.code_in, .code_out = cmd->redir.code_out};
	clr(cmd);
	if (cmd->redir.code_in & S_LEFT)
	{
		cmd->fd[0] = open(str, O_RDONLY, 0777);
		if (cmd->fd[0] < 0)
		{
			printf("%s:%s:%s\n", PRMT, MSGE12, str);
			r.code_in = -1;
			err_msg(MSGE4, 0, d);
			// exit ?
		}
	}
	if (cmd->redir.code_in & D_LEFT)
	{
		// while (ft_strcmp(input, str))
		// {input new line}
	}
	if (cmd->redir.code_out & S_RIGHT)
	{
		cmd->fd[1] = open(str, O_WRONLY, 0777);
		if (cmd->fd[1] < 0)
		{
			printf("%s:%s:%s\n", PRMT, MSGE4, str);
			r.code_out = -1;
			err_msg(MSGE4, 0, d);
			// exit ? 
		}
	}
	if (cmd->redir.code_out & D_RIGHT)
	{
		cmd->fd[1] = open(str, O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (cmd->fd[1] < 0)
		{
			printf("%s:%s:%s\n", PRMT, MSGE4, str);
			r.code_out = -1;
			err_msg(MSGE4, 0, d);
			// exit ?
		}
	}
	return (r);
} */