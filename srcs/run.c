#include "minishell.h"

void	cmd1(t_d *d)
{
	if (d->cmd.path)
	{
		if (execve(d->cmd.path, d->cmd.arg, d->cmd.env) == -1)
		{
			perror(MSGE8);
			strerror(errno);
			exit(errno);
		}
		exit(0);
	}
	err(8, d);
}

void	wait_chailds(t_d *d)
{
	int	res;

	res = waitpid(d->cmd_pid, &d->stat, 0);
	if (res < 0)
		out_msg(MSGE7, 0);
	if (d->stat)
		out_msg(MSGE8, 0);
	d->cmd.code_ret = res;
}


int	cmd0(t_d *d)
{
	d->cmd_pid = fork();
	if_err_exit(d->cmd_pid, 5, d);
	if (d->cmd_pid)
		wait_chailds(d);
	else
		cmd1(d);
	return (d->cmd.code_ret);
}


/*
**	run bash
*/

int		run(char *str)
{
	t_d		d;
	int		res;

	res = 0;

	if (str)
	{
		d.cmd.path = "/bin/bash";
		d.cmd.arg = malloc(sizeof(char *) * 4);
		d.cmd.arg[0] = ft_strdup("minishell");
		d.cmd.arg[1] = ft_strdup("-c");
		d.cmd.arg[2] = str;
		d.cmd.arg[3] = NULL;
		cmd0(&d);
		free(d.cmd.arg[0]);
		free(d.cmd.arg[1]);
		free(d.cmd.arg);
	}
	return (res);
}

int		exec_cmd(t_d *d)
{
	int	code;

	code = 0;
	// redirections
	if (d->cmd.redir.code_in || d->cmd.redir.code_out)
	{
		// redir;
	}
	// pipes
	if (d->cmd.pipe)
	{
		// pipes
	}
	// fork

	// execve
	// return fd
	return (code);	// 0
}

int		exec_cmds(t_cmds *cmds)
{
	int	code;

	code = 0;
	while (cmds->cmd->type)
	{
		cmds->d->cmd = *cmds->cmd;
		code = exec_cmd(cmds->d);
		if (code)
			return (code);
		cmds++;
	}
	return (code);	// 0
}
