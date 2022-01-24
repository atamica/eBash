#include "minishell.h"

int	type_cmd(char *cmd)
{
	if (is_builtins(cmd))
		return (BUILTINS);
	if (is_ext_cmd(cmd))
		return (EXTERNALS);
	return (OTHERS);
}

int	run_builtins_cmd(t_d *d, t_cmd *cmd)
{
	int		res;

	res = 0;
	if (cmd->type == BUILTINS)
	{
		if (!ft_strncmp(cmd->path, "cd", 3))
			return (ft_cd(cmd));
		if (!ft_strncmp(cmd->path, "echo", 5))
			return (ft_echo(cmd));
		if (!ft_strncmp(cmd->path, "pwd", 4))
			return (ft_pwd(cmd));
		if (!ft_strncmp(cmd->path, "env", 4))
			return (ft_env(d, cmd));
		if (!ft_strncmp(cmd->path, "export", 7))
			return (ft_export(d, cmd));
		if (!ft_strncmp(cmd->path, "exit", 5))
			return (ft_exit(cmd));
		if (!ft_strncmp(cmd->path, "unset", 6))
			return (ft_unset(cmd->arg[1], d));
	}
	return (res);
}
