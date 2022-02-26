#include "minishell.h"

static char	*pth(char *ptr, char **env, t_d *d)
{
	char	*cur_dir;
	char	*path;

	path = NULL;
	if (ptr)
	{
		cur_dir = get_current_dir();
		if (*ptr == '~')
			path = ft_strjoin_c(getenv("HOME"), ptr + 1, SL);
		else if (*ptr == SL)
			path = ft_strdup(ptr);
		else if (!ft_strncmp(ptr, "-", 2))
			path = get_env_val(env, OLD_DIR);
		else
			path = ft_strjoin_c(getcwd(cur_dir, LEN_PATH), ptr, SL);
		set_env_val(OLD_DIR, cur_dir, d);
		free(cur_dir);
	}
	return (path);
}

int	ft_cd(t_cmd *cmd, t_d *d)
{
	char	*path;
	int		res;

	res = 0;
	if (cmd->arg) 
	{
		if (cmd->arg[1])
		{
			if (cmd->arg[2])
			{
				ft_putendl_fd(TOO_MANY_ARGS, cmd->fd[3]);
				return (1);
			}
			path = pth(cmd->arg[1], cmd->env, d);
			if (!path)
				return (2);
		}
		else
			path = ft_strdup(getenv("HOME"));
		if_err_cd(res = chdir(path), cmd->fd[3], path);
		free(path);
	}
	return (-res);
}
