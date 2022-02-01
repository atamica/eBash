#include "minishell.h"

static char	*pth(char *ptr)
{
	char	*tmp;
	char	*path;

	path = NULL;
	tmp = malloc(LEN_PATH);
	if (!tmp)
		return (tmp);
	if (ptr && *ptr == '~')
		path = ft_strjoin_c(getenv("HOME"), ptr + 1, SL);
	else
		path = ft_strjoin_c(getcwd(tmp, LEN_PATH), ptr, SL);
	free(tmp);
	return (path);
}

int	ft_cd(t_cmd *cmd)
{
	char	*path;
	int		res;

	path = NULL;
	if (cmd->arg && cmd->arg[1] && cmd->arg[2])
	{
		ft_putendl_fd(TOO_MANY_ARGS, cmd->fd[3]);
		return (1);
	}
	if (cmd->arg && cmd->arg[1])
	{
		if (cmd->arg[1][0] == SL)
			path = ft_strdup(cmd->arg[1]);
		else
			path = pth(cmd->arg[1]);
		if (!path)
			return (2);
	}
	if (cmd->arg && !cmd->arg[1])
		path = ft_strdup(getenv("HOME"));
	if_err_cd(res = chdir(path), cmd->fd[3], path);
	free(path);
	return (-res);
}
