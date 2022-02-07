#include "minishell.h"

int	type_cmd(char *cmd)
{
	if (!cmd)
		return (EMPTY);
	if (is_builtins(cmd))
		return (BUILTINS);
	if (is_ext_cmd(cmd))
		return (EXTERNALS);
	return (OTHERS);
}

static	t_fout	fd_out(t_cmd *cmd, int *pipe_out)
{
	t_fout	res;

	if (pipe_out && (cmd->fd[1] == OUT))
		res = (t_fout){.fl_close = 0, .fd = pipe_out[1]};
	else
		res = (t_fout){.fl_close = (cmd->fd[1] != OUT), .fd = cmd->fd[1]};
	return (res);
}

int	run_builtins_cmd(t_d *d, t_cmd *cmd, int *pipe_out)
{
	int		res;
	t_fout	fout;

	res = 0;
	fout = fd_out(cmd, pipe_out);
	if (cmd->type == BUILTINS)
	{
		if (!ft_strncmp(cmd->path, "cd", 3))
			res = ft_cd(cmd);
		else if (!ft_strncmp(cmd->path, "echo", 5))
			res = ft_echo(cmd, fout.fd);
		else if (!ft_strncmp(cmd->path, "pwd", 4))
			res = ft_pwd(cmd);
		else if (!ft_strncmp(cmd->path, "env", 4))
			res = ft_env(d, fout.fd);
		else if (!ft_strncmp(cmd->path, "export", 7))
			res = ft_export(d, fout.fd, cmd->arg, cmd->env);
		else if (!ft_strncmp(cmd->path, "exit", 5))
			res = ft_exit(cmd, d);
		else if (!ft_strncmp(cmd->path, "unset", 6))
			res = ft_unset(d, cmd->arg);
		close_if(fout);
	}
	return (res);
}
