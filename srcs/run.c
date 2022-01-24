#include "minishell.h"

#ifdef NDEBUG_RUN

/*
**	run bash
*/

int	run(t_d *d)
{
	d->stat = 0;
	if (d->input)
	{
		d->cmd.code_ret = 0;
		d->cmd.path = "/bin/bash";
		d->cmd.arg = malloc(sizeof(char *) * 4);
		d->cmd.arg[0] = "minishell";
		d->cmd.arg[1] = "-c";
		d->cmd.arg[2] = d->input;
		d->cmd.arg[3] = NULL;
		if_err_exit(d->cmd_pid = fork(), 5, d);
		if (d->cmd_pid)
			if_err_exit(waitpid(d->cmd_pid, &d->stat, 0), 7, d);
		else if (d->cmd.path)
		{
			if_err_exit(execve(d->cmd.path, d->cmd.arg, d->cmd.env), errno, d);
			exit(SUCCSESS);
		}
			free(d->cmd.arg);
	}
	return (d->stat);
}
#endif
