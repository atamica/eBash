#include "minishell.h"

void	cmd1_cmd(t_d *d, t_cmd *cmd)
{
	if (cmd->path)
	{
printf("cmd_cmd: path=%s ", cmd->path);
print_param(cmd->arg, "_", ' ');
printf(N);
		if (execve(cmd->path, cmd->arg, cmd->env) == -1)
		{
			perror(MSGE8);
			strerror(errno);
			exit(errno);
		}
		exit(0);
	}
	err(8, d);
}

void	wait_chailds_cmd(t_d *d)
{
	int	res;

	res = waitpid(d->cmd_pid, &d->stat, 0);
	if (res < 0)
		out_msg(MSGE7, 0);
	if (d->stat)
		out_msg(MSGE8, 0);
	//d->cmd.code_ret = res;
}


int	cmd_cmd(t_d *d, t_cmd *cmd)
{
	d->cmd_pid = fork();
	if_err_exit(d->cmd_pid, 5, d);
	if (d->cmd_pid)
		wait_chailds_cmd(d);
	else
		cmd1_cmd(d, cmd);
	return (d->stat);
}