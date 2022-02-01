#include "minishell.h"

int	cmd_cmd(t_d *d, t_cmd *cmd, int *pipe_in, int *pipe_out)
{
	if_err_exit(d->cmd_pid = fork(), 5, d);
	if (d->cmd_pid)
	{
		close_f2any(pipe_in);
		close_files_rd(cmd);
		if_err_exit(waitpid(d->cmd_pid, &d->stat, 0), 7, d);
	}
	else if (cmd->path)
	{
		if (cmd->code_red & D_LEFT)
			prepare_hdoc_pipe(cmd, d, pipe_in);
		dup_io(cmd->fd, d, pipe_in, pipe_out);
		if_err_exit(execve(cmd->path, cmd->arg, cmd->env), errno, d);
		exit(SUCCSESS);
	}
	return (d->stat);
}
