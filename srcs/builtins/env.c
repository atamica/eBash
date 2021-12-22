/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 09:01:48 by atamica           #+#    #+#             */
/*   Updated: 2021/11/07 09:01:52 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_env_list(char **env)
{
	int	r;

	r = 0;
	if (env)
	{
		while (env[r])
			r++;
	}
	return (r);
}

int	ft_env(t_d *d)
{
	print_param(d->env, "", '\n');
	printf(N);
	return (0);
}

char	*get_env_val(char **env, char *name)
{
	return (ft_strdup(is_in_env_list(env, name).val));
}

int	copy_envs(t_d *d)
{
	int		res;

	res = 0;
	if (d->env_ex)
	{
		d->env = malloc((1 + len_env_list(d->env_ex)) * sizeof(char *));
		if_err_fatal(d->env, 2, d);
		while (d->env_ex[res])
		{
			d->env[res] = ft_strdup(d->env_ex[res]);
			res++;
		}
		d->env[res] = NULL;
	}
	return (res);
}
