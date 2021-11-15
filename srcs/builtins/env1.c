/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 09:01:58 by atamica           #+#    #+#             */
/*   Updated: 2021/11/07 09:02:01 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_env(char *name, char *val, t_d *d)
{
	free(d->env_in);
	d->env_in = (char **)malloc(2 * sizeof(char *));
	if_err_fatal(d->env_in, d);
	*d->env_in = ft_strjoin_c(name, val, '=');
	if_err_fatal(*d->env_in, d);
	d->env_in[1] = NULL;
}

static void	replase_env(char *name, char *val, t_d *d, t_val *r)
{
	free(d->env_in[r->position]);
	d->env_in[r->position] = ft_strjoin_c(name, val, '=');
	if_err_fatal(d->env_in[r->position], d);
}

static void	paste_env(char *name, char *val, t_d *d)
{
	int		i;
	char	**tmp;

	tmp = (char **)malloc((len_env_list(d->env_in) + 1) * sizeof(char *));
	if_err_fatal(tmp, d);
	i = 0;
	while (*(d->env_in + i))
	{
		*(tmp + i) = *(d->env_in + i);
		i++;
	}
	tmp[i] = ft_strjoin_c(name, val, '=');
	if_err_fatal(tmp[i], d);
	tmp[i + 1] = NULL;
	free(d->env_in);
	d->env_in = tmp;
}

static void	cut_env(t_d *d, t_val *r)
{
	char	**tmp;
	char	**cpy;

	tmp = d->env_in;
	cpy = tmp + r->position;
	while (*cpy)
	{
		*cpy = *(cpy + 1);
		cpy++;
	}
	free(tmp[r->position]);
}

void	set_env_val(char *name, char *val, t_d *d)
{
	t_val	r;

	if (name)
	{
		r = is_in_env_list(d->env_in, name);
		if (val)
		{
			if (d->env_in && !*d->env_in)
				create_env(name, val, d);
			else if (r.present)
				replase_env(name, val, d, &r);
			else
				paste_env(name, val, d);
		}
		else
		{
			if (r.present)
				cut_env(d, &r);
		}
	}
}
