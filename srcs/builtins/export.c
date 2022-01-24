#include "minishell.h"

int	ft_export(t_d *d, t_cmd *cmd)
{
	print_param_fd(d->env, "declare -x ", '\n', cmd->fd[1]);
	return (0);
}
