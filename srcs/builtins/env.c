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

int	ft_env(t_d *d, int fd)
{
	print_param_fd(d->env, "", '\n', fd);
	ft_putstr_fd(N, fd);
	return (0);
}

char	*get_env_val(char **env, char *name)
{
	return (ft_strdup(is_in_env_list(env, name).val));
}

int	copy_envs(char **env_ex, t_d *d)
{
	int		res;

	res = 0;
	if (env_ex)
	{
		d->env = malloc((1 + len_env_list(env_ex)) * sizeof(char *));
		if_err_fatal(d->env, 2, d);
		while (env_ex[res])
		{
			d->env[res] = ft_strdup(env_ex[res]);
			res++;
		}
		d->env[res] = NULL;
	}
	return (res);
}
