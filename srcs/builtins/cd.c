#include "minishell.h"

int	cd(t_cmd *cmd)
{
	char	*path;
	int		res;

	if (!(cmd->arg[1] && ft_strncmp(cmd->arg[1], "~", 2)))
		path = getenv("HOME");
	else if (ft_strncmp(cmd->arg[1], "-", 2))
	{
		// cd previous dir
		// cd ppwd
	}
	else if (cmd->arg[1][0] ==  '/')// cd abs dir
		path = ft_strdup(cmd->arg[1]);
	else	// cd dir
		path = ft_strjoin_m(getenv("PWD"), cmd->arg[1]);
	res = chdir(path);
	if (res)
	{
		ft_putstr_fd("/nminishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Нет такого файла или каталога", 2);
	}
	free(path);
	return (res);
}

int	check_builtins(char *cmd)
{
	int		res;
	t_cmd	cmd_b;

	res = 0;
	if (ft_strncmp(cmd, "cd", 2) && ((cmd[2] == ' ') || !cmd[2]))
	{
		cmd_b.arg = ft_split(cmd, ' ');
		res = cd(&cmd_b);
	}
	return (res);
}