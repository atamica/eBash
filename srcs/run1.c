#include "minishell.h"

static	void	err0(char *msg1, char *msg2, int code, t_d *d)
{
	write (2, msg1, ft_strlen(msg1));
	if (msg2)
	{
		write(2, " ", 1);
		write(2, msg2, ft_strlen(msg2));
	}
	write(2, N, 1);
	if (d)
		free_d(d);
	if (code)
		exit(code);
}


static	void	ddup(int *p, int i, t_d *d)
{
	if (dup2(p[i], i) < 0)
		err0(ERR_FATAL, NULL, 1, d);	//	err_msg(char *msg, int code, t_d *d)
	close(p[i]);
}

static	void	redirect_io(int *p, int *t, int i, t_d *d)
{
	t[i] = dup(i);
	ddup(p, i, d);
}

static	void	restore_io(int *t, int i, int *fl, t_d *d)
{
	ddup(t, i, d);
	*fl = i;
}

int	cycle(t_cmds *cmds, t_d *d)
{
	t_f	fl;
	pid_t	pid;

	fl = (t_f){0,0};
	if (cmds)
	{
		while (cmds->cmd->type)
		{
			d->cmd = *cmds->cmd;
			if ((cmds + 1)->cmd->type)
				fl.pip = 1;
			else
				fl.pip = 0;
			if (fl.io)
				redirect_io(cmds->cmd->fd, cmds->cmd->fds, STDIN_FILENO, d);
			if (fl.pip)
			{
				if (pipe(cmds->cmd->fd))
					err0(ERR_FATAL, NULL, 1, d);
				redirect_io(cmds->cmd->fd, cmds->cmd->fds, STDOUT_FILENO, d);
			}
			if (d->cmd.path && (d->cmd.type == EXTERNALS))
			{
				pid = fork();
				if (pid < 0)
					err0(ERR_FATAL, NULL, 1, d);
				else if (!pid)
				{
					if (execve(*cmds->cmd->arg, cmds->cmd->arg, d->cmd.env))
						err0(ERR_EXE, *cmds->cmd->arg, 0, d);
					exit(0);
				}
				waitpid(pid, &cmds->cmd->code_ret, 0);
			}
			else if (d->cmd.type == BUILTINS)
				d->stat = run_builtins(d);
			if (fl.io)
				restore_io(cmds->cmd->fds, STDIN_FILENO, &fl.io, d);
			if (fl.pip)
				restore_io(cmds->cmd->fds, STDOUT_FILENO, &fl.io, d);
			d->cmd.code_ret = cmds->cmd->code_ret;
			cmds++;
		}
	}
	return (0);
}
