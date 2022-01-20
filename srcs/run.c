#include "minishell.h"

/* 
int	cmd(t_d *d, t_cmd *cmd)
{
	if_err_exit(d->cmd_pid = fork(), 5, d);
	if (d->cmd_pid)
		if_err_exit(waitpid(d->cmd_pid, &d->stat, 0), 7, d);
	else if (cmd->path)
	{
		if_err_exit(execve(cmd->path, cmd->arg, cmd->env), errno, d);
		exit(SUCCSESS);
	}
	return (d->stat);
}
*/

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

/* 
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
*/

/* 
void	cmd1(t_d *d)
{
	if (d->cmd.path)
	{
		if (execve(d->cmd.path, d->cmd.arg, d->cmd.env) == -1)
		{
			perror(MSGE8);
			exit(errno);
		}
		exit(0);
	}
	err(8, d);
}

void	wait_chailds(t_d *d)
{
	d->cmd.code_ret = waitpid(d->cmd_pid, &d->stat, 0);
	if (d->cmd.code_ret < 0)
		out_msg(MSGE7, 0);
	if (d->stat)
		out_msg(MSGE8, 0);
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
*/
