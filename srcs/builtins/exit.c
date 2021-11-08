/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 09:49:46 by atamica           #+#    #+#             */
/*   Updated: 2021/11/07 09:49:51 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_code_msg(t_d *d, char *msg, int code)
{
	printf("%s: %s: %s: %s\n", PRMT, d->cmd.arg[0], d->cmd.arg[1], msg);
	return (code);
}

int	ft_exit(t_d *d)
{
	int	code_exit;

	code_exit = 0;
	printf("exit\n");
	if (d->cmd.arg[1])
	{
		if (is_only_digits(d->cmd.arg[1]))
		{
			if (d->cmd.arg[2])
				code_exit = set_code_msg(d, MSGE10, -1);
			else
				code_exit = (unsigned int)ft_atoi(d->cmd.arg[1]) % 256;
		}
		else
			code_exit = set_code_msg(d, MSGE11, 2);
	}
	if (code_exit >= 0)
	{
		free_d(d);
		exit(code_exit);
	}
	return (0);
}
