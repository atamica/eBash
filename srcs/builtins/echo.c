#include "minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	fl;

	fl = (cmd->arg && !ft_strncmp(*(cmd->arg + 1), "-n", 3));
	print_param_fd(cmd->arg + fl + 1, MSG0, ' ', STDOUT_FILENO);
	if (!fl)
		printf(N);
	return (0);
}
