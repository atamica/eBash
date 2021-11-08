#include "minishell.h"

char	*ft_strjoin_c(char const *s1, char const *s2, char c)
{
	char	*r;
	size_t	l1;
	size_t	l2;
	int		size_c;

	if (s1 && s2)
	{
		size_c = (c != 0);
		l1 = ft_strlen(s1);
		l2 = ft_strlen(s2);
		r = (char *)malloc((l1 + l2 + 1 + size_c) * sizeof(char));
		if (r)
		{
			ft_strlcpy(r, s1, l1 + 1);
			if (size_c)
				*(r + l1) = c;
			ft_strlcpy(r + l1 + size_c, s2, l2 + 1);
			return (r);
		}
	}
	return (NULL);
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

	paths = ft_split(getenv("PATH"), ':');
	cmd_path = NULL;
	if (paths)
	{
		tmp = paths;
		while (*tmp && !cmd_path)
		{
			cmd_path = ft_strjoin_m(*tmp++, cmd);
			if (is_file_exist(cmd_path) != 1)
				free_null((void **)&cmd_path);
		}
		free2(paths);
	}
	if (!cmd_path && (is_file_exist(cmd) == 1))
		cmd_path = ft_strdup(cmd);
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

void	print_param(char **arg, char *prefix, char separator)
{
	char	c;
	int		i;
	
	if (arg)
	{
		if (prefix && *prefix)
			c = '"';
		else
			c = 0;
		i = 0;
		while (arg[i])
		{
			printf("%s%c%s%c%c", prefix, c, arg[i], c, separator);
			i++;
		}
	}
}

char	*prompt(t_d *d)
{
	char	*user;
	char	*path;
	char	p[LEN_PATH];
	size_t	len;

	user = get_env_val(d->env_in, "USER");
	path = getcwd(p, LEN_PATH);
	len = ft_strlen(GREEN) + ft_strlen(user) + ft_strlen(RESET) + \
			ft_strlen(BLUE) + ft_strlen(path) + ft_strlen(RESET) + 3;
	d->prompt = (char *)malloc(len);
	if_err_fatal(d->prompt, d);
	len = ft_strlen(GREEN);
	ft_memcpy(d->prompt, GREEN, ft_strlen(GREEN));
	ft_memcpy(d->prompt + len, user, ft_strlen(user));
	len += ft_strlen(user);
	ft_memcpy(d->prompt + len, RESET, ft_strlen(RESET));
	len += ft_strlen(RESET);
	*(d->prompt + len++) = ':';
	ft_memcpy(d->prompt + len, BLUE, ft_strlen(BLUE));
	len += ft_strlen(BLUE);
	ft_memcpy(d->prompt + len, path, ft_strlen(path));
	len += ft_strlen(path);
	ft_memcpy(d->prompt + len, RESET, ft_strlen(RESET));
	len += ft_strlen(RESET);
	ft_memcpy(d->prompt + len, "$", 2);
	free(user);
	return (d->prompt);
}