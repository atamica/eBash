#include "minishell.h"

void	cmd1_cmd(t_d *d, t_cmd *cmd)
{
	if (cmd->path)
	{
/* printf("cmd_cmd: path=%s ", cmd->path);
print_param(cmd->arg, "_", ' ');
printf(N); */
		dup_io(cmd->fd, d);
		if (execve(cmd->path, cmd->arg, cmd->env) == -1)
		{
			perror(MSGE8);
			//strerror(errno);
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

int	exe(t_exe *cmde, t_d *d)
{
	int		pid;

	cmde->code = 0;
	if_err_exit(pid = fork(), 5, d);
	if (pid)
	{// parent
		if_err_exit(waitpid(pid, &cmde->code, 0), 7, d);
		//if_err_no_fatal(cmde->code, 8, d);
		//	perror(MSGE8);
	}
	else
	{// child
		dup_io(cmde->fd, d);
		if (execve(cmde->path, cmde->args, cmde->env) == -1)
		{
			perror(MSGE8);
			exit(errno);
		}
		exit(0);
	}
	return (cmde->code);
}