#include "minishell.h"

int	ft_export(t_d *d)
{
	print_param(d->env, "declare -x ", '\n');
	return (0);
}
