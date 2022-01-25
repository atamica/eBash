#include "minishell.h"

static int	set_code_msg(t_cmd *cmd, char *msg, int code)
{
	ft_putstr_fd(PRMT, cmd->fd[3]);
	ft_putstr_fd(": ", cmd->fd[3]);
	ft_putstr_fd(cmd->arg[0], cmd->fd[3]);
	ft_putstr_fd(": ", cmd->fd[3]);
	ft_putstr_fd(cmd->arg[1], cmd->fd[3]);
	ft_putstr_fd(": ", cmd->fd[3]);
	ft_putendl_fd(msg, cmd->fd[3]);
	return (code);
}

int	ft_exit(t_cmd *cmd)
{
	int	code_exit;

	code_exit = 0;
	ft_putendl_fd("exit", cmd->fd[3]);
	if (cmd->arg[1])
	{
		if (is_only_digits(cmd->arg[1]))
		{
			if (cmd->arg[2])
				code_exit = set_code_msg(cmd, MSGE10, -1);
			else
				code_exit = (unsigned int)ft_atoi(cmd->arg[1]) % 256;
		}
		else
			code_exit = set_code_msg(cmd, MSGE11, 2);
	}
	if (code_exit >= 0)
		exit(code_exit);
	return (0);
}
