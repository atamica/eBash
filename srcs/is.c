#include "minishell.h"

int	is_builtins(char *cmd)
{
	return (!((ft_strncmp(cmd, "cd", 3) && ft_strncmp(cmd, "echo", 5) && \
		ft_strncmp(cmd, "pwd", 4) && ft_strncmp(cmd, "export", 7) && \
		ft_strncmp(cmd, "unset", 6) && ft_strncmp(cmd, "env", 4) && \
		ft_strncmp(cmd, "exit", 5))));
}

int	is_ext_cmd(char *cmd)
{
	char	*tmp;

	tmp = cmdf(cmd);
	if (tmp)
	{
		free(tmp);
		return (1);
	}
	return (0);
}

int	is_dir(char *path)
{
	struct stat	st;

	if (path)
	{
		if (stat(path, &st) < 0)
			return (-1);
		if (S_ISDIR(st.st_mode))
			return (1);
	}
	return (0);
}

int	is_file_exist(char *path)
{
	struct stat	st;

	if (path)
	{
		if (stat(path, &st) < 0)
			return (-1);
		if (S_ISREG(st.st_mode))
			return (1);
	}
	return (0);
}

t_val	is_in_env_list(char **env, char *name)
{
	int		i;
	size_t	len;
	t_val	res;

	res = (t_val){.present = 0, .position = 0, .val = NULL};	// {0,0,NULL}
	if (env && name)
	{
		i = 0;
		len = ft_strlen(name);
		while (env[i])
		{
			if (!ft_strncmp(env[i], name, len) && (env[i][len] == '='))
			{
				res = (t_val){.present = 1, .position = i, \
								.val = env[i] + len + 1};
				break ;
			}
			i++;
		}
	}
	return (res);
}
