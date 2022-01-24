#include "minishell.h"

int	cmd_cmd(t_d *d, t_cmd *cmd, int *pipe_in, int *pipe_out)
{
	if_err_exit(d->cmd_pid = fork(), 5, d);
	if (d->cmd_pid)
	{
		close_f2any(pipe_in);
		if_err_exit(waitpid(d->cmd_pid, &d->stat, 0), 7, d);
	}
	else if (cmd->path)
	{
		dup_io(cmd->fd, d, pipe_in, pipe_out);
		if_err_exit(execve(cmd->path, cmd->arg, cmd->env), errno, d);
		exit(SUCCSESS);
	}
	return (d->stat);
}
