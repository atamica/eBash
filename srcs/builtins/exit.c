#include "minishell.h"

static int	set_code_msg(t_cmd *cmd, char *msg, int code)
{
	printf("%s: %s: %s: %s\n", PRMT, cmd->arg[0], cmd->arg[1], msg);
	return (code);
}

int	ft_exit(t_cmd *cmd)
{
	int	code_exit;

	code_exit = 0;
	printf("exit\n");
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
