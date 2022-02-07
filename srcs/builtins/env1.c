#include "minishell.h"

static void	create_env(char *name, char *val, t_d *d)
{
	free(d->env);
	d->env = (char **)malloc(2 * sizeof(char *));
	if_err_fatal(d->env, 2, d);
	*d->env = ft_strjoin_c(name, val, '=');
	if_err_fatal(*d->env, 2, d);
	d->env[1] = NULL;
}

static void	replace_env(char *name, char *val, t_d *d, t_val *r)
{
	free(d->env[r->position]);
	d->env[r->position] = ft_strjoin_c(name, val, '=');
	if_err_fatal(d->env[r->position], 2, d);
}

static void	paste_env(char *name, char *val, t_d *d)
{
	int		i;
	char	**tmp;

	tmp = malloc((len_env_list(d->env) + 2) * sizeof(char *));
	if_err_fatal(tmp, 2, d);
	i = 0;
	while (*(d->env + i))
	{
		*(tmp + i) = *(d->env + i);
		i++;
	}
	if_err_fatal(tmp[i] = ft_strjoin_c(name, val, EQ), 2, d);
	tmp[++i] = NULL;
	free(d->env);
	d->env = tmp;
}

static void	cut_env(t_d *d, t_val *r)
{
	char	**ptr;

	ptr =  d->env + r->position;
	free(*ptr);
	while (*ptr)
	{
		*ptr = *(ptr + 1);
		ptr++;
	}
}

void	set_env_val(char *name, char *val, t_d *d)
{
	t_val	r;

	if (name)
	{
		r = is_in_env_list(d->env, name);
		if (val)
		{
			if (d->env && !*d->env)
				create_env(name, val, d);
			else if (r.present)
				replace_env(name, val, d, &r);
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
