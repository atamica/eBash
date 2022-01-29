#include "minishell.h"

void	prepare_hdoc(t_cmd *cmd, t_d *d)
{
	int		pipe_hd[2];
	int		stat;
	pid_t	pid_hd;


	if_err_exit(pipe(pipe_hd), 3, d);
	if_err_exit(pid_hd = fork(), 5, d);
	if (!pid_hd)
	{
		close_f(pipe_hd[0]);
		h_doc(pipe_hd[1], cmd, d);
		close_f(pipe_hd[1]);
		free_cmd(cmd);
		free_d(d);
		exit(0);
	}
	dup2(pipe_hd[0], IN);
	close_f2(pipe_hd);
	if_err_exit(waitpid(pid_hd, &stat, 0), 7, d);
}	

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
		{
			prepare_hdoc(cmd, d);
		}
		dup_io(cmd->fd, d, pipe_in, pipe_out);
		if_err_exit(execve(cmd->path, cmd->arg, cmd->env), errno, d);
		exit(SUCCSESS);
	}
	return (d->stat);
}
