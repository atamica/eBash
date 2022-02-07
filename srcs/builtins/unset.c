#include "minishell.h"

int	ft_unset(t_d *d, char **args)
{
	while (args && *args)
		set_env_val(*args++, NULL, d);
	return (0);
}
