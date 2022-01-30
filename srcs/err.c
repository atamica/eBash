/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 09:53:41 by atamica           #+#    #+#             */
/*   Updated: 2021/11/07 09:53:50 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_msg(char *msg, int code, t_d *d)
{
	write(2, msg, ft_strlen(msg));
	if (code > 1)
		free_d(d);
	if (code)
		exit(code);
}

char	*msg_error(int code)
{
	if (code == 1)
		return (MSGE1);
	if (code == 2)
		return (MSGE2);
	if (code == 3)
		return (MSGE3);
	if (code == 4)
		return (MSGE4);
	if (code == 5)
		return (MSGE5);
	if (code == 6)
		return (MSGE6);
	if (code == 7)
		return (MSGE7);
	if (code == 8)
		return (MSGE8);
	if (code == 9)
		return (MSGE9);
	if (code == 14)
		return (MSGE14);
	return (MSG0);
}

void	err(int code, t_d *d)
{
	err_msg(msg_error(code), code, d);
}

void	if_err_exit(int er, int code, t_d *d)
{
	if (er < 0)
		err(code, d);
}

void	if_err_no_fatal(int er, int code, t_d *d)
{
	if (er)
		err_msg(msg_error(code), 0, d);
}

int	out_msg(char *msg, int code)
{
	perror(msg);
	return (code);
}

void	if_err_fatal(void *ptr, int code, t_d *d)
{
	if (!ptr)
		err(code, d);
}

int		syntax_err(char c)
{
	printf("%s: %s «%c»\n", PRMT, MSGE13, c);
	return (2);
}

int	err_open(int fd, t_d *d)
{
	if (fd < 0)
	{
		err_msg(MSGE4, 0, d);
		return (ERROR);
	}
	return (SUCCSESS);
}