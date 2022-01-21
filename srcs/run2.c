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

/* 
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
*/