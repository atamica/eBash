#include "minishell.h"

static	void	set_values(t_d *d, char **args, char **env)
{
	char	*name;
	char	*val;
	char	*ptr;

	while (args && *args)
	{
		ptr = get_pos_char(*args, '=');
		if (ptr)
		{
			name = ft_substr(*args, 0, ptr++ - *args);
			val = strip_quo(ft_strdup(ptr), env, 1);
			set_env_val(name, val, d);
			free(val);
			free(name);
		}
		args++;
	}
}

int	ft_export(t_d *d, int fd, char **args, char **env)
{
	char	**ptr;
	char	*str;

	if (args++ && *args)
		set_values(d, args, env);
	else
	{
		ptr = d->env;
		while (ptr && *ptr)
		{
			str = ft_strchr(*ptr, '=') + 1;
			if (str)
			{
				ft_putstr_fd("declare -x ", fd);
				write(fd, *ptr, str - *ptr);
				ft_putchar_fd(DQ, fd);
				ft_putstr_fd(str, fd);
				ft_putendl_fd("\"", fd);
			}
			ptr++;
		}
	}
	return (0);
}
