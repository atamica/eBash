#include "minishell.h"

int	type_cmd(char *cmd)
{
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

	res = 0;
	if (cmd->type == BUILTINS)
	{
		if (!ft_strncmp(cmd->path, "cd", 3))
			return (ft_cd(cmd));
		if (!ft_strncmp(cmd->path, "echo", 5))
			return (ft_echo(cmd, fd_out(cmd, pipe_out)));
		if (!ft_strncmp(cmd->path, "pwd", 4))
			return (ft_pwd(cmd));
		if (!ft_strncmp(cmd->path, "env", 4))
			return (ft_env(d, fd_out(cmd, pipe_out)));
		if (!ft_strncmp(cmd->path, "export", 7))
			return (ft_export(d, fd_out(cmd, pipe_out)));
		if (!ft_strncmp(cmd->path, "exit", 5))
			return (ft_exit(cmd));
		if (!ft_strncmp(cmd->path, "unset", 6))
			return (ft_unset(cmd->arg[1], d));
	}
	return (res);
}
