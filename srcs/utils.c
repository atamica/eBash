#include "minishell.h"

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

int	file_exist(char *path)
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

char	*ft_strjoin_m(char const *s1, char const *s2)
{
	char	*r;
	size_t	l1;
	size_t	l2;

	if (s1 && s2)
	{
		l1 = ft_strlen(s1);
		l2 = ft_strlen(s2);
		r = (char *)malloc((l1 + l2 + 2) * sizeof(char));
		if (r)
		{
			ft_strlcpy(r, s1, l1 + 1);
			*(r + l1) = '/';
			ft_strlcpy(r + l1 + 1, s2, l2 + 1);
			return (r);
		}
	}
	return (NULL);
}

char	*cmdf(char *cmd)
{
	char	*cmd_path;
	char	**paths;
	char	**tmp;

	if ((file_exist(cmd) == 1) || check_builtins(cmd))
		return (ft_strdup(cmd));
	paths = ft_split(getenv("PATH"), ':');
	cmd_path = NULL;
	if (paths)
	{
		tmp = paths;
		while (*tmp && !cmd_path)
		{
			cmd_path = ft_strjoin_m(*tmp++, cmd);
			if (file_exist(cmd_path) != 1)
				free_null((void **)&cmd_path);
		}
		free2(paths);
	}
	return (cmd_path);
}

void	dup2_check(int old_fd, int new_fd, t_d *d)
{
	if (new_fd != old_fd)
	{
		if (dup2(old_fd, new_fd) != new_fd)
			err(6, d);
		close_f(old_fd);
	}
}

void	print_param(char **arg)
{
	if (arg)
	{
		while (*arg)
			printf("(%s) ", *arg++);
	}
}