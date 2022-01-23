#include "minishell.h"

int	ft_unset(char *name, t_d *d)
{
	set_env_val(name, NULL, d);
	return (0);
}
