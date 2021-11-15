/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:00:10 by atamica           #+#    #+#             */
/*   Updated: 2021/11/07 10:00:14 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	is_inside(char *arg)
{
	return (arg && strcmp(arg, P) && strcmp(arg, T));
} */

int	is_qu(t_fl *fl)
{
	return (fl->fl_s_qu || fl->fl_d_qu);
}

int	is_fl(t_fl *fl)
{
	return (fl->fl_s_qu || fl->fl_d_qu || fl->fl_dol);
}

int	is_only_digits(char *str)
{
	int	r;

	r = 0;
	if (str)
	{
		if (*str == '-' || *str == '+')
			str++;
		r = ft_isdigit(*str);
		while (*str)
		{
			if (!ft_isdigit(*str))
				return (0);
			str++;
		}
	}
	return (r);
}

int	is_in_name(char *str)
{
	return ((*(str) == '_') || ft_isalnum(*(str)));
}