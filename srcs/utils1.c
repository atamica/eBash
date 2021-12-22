#include "minishell.h"

char	*prompt(t_d *d)
{
	char	*user;
	char	*path;
	char	p[LEN_PATH];
	size_t	len;

	user = get_env_val(d->env, "USER");
	path = getcwd(p, LEN_PATH);
	len = ft_strlen(GREEN) + ft_strlen(user) + ft_strlen(RESET) + \
			ft_strlen(BLUE) + ft_strlen(path) + ft_strlen(RESET) + 3;
	d->prompt = (char *)malloc(len);
	if_err_fatal(d->prompt, 2, d);
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

size_t	sp_count(char *ptr)
{
	size_t	l;

	l = 0;
	if (ptr)
	{
		while(ptr[l] && ft_isalsp(ptr[l]))
			l++;
	}
	return (l);
}

char	*skip_spa(char *ptr)
{
	if (ptr)
	{
		while (*ptr && ft_isalsp(*ptr))
			ptr++;
	}
	return (ptr);
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
			if (!arg[i + 1])
				separator = 0;
			printf("%s%c%s%c%c", prefix, c, arg[i++], c, separator);
		}
	}
}

void	print_param_fd(char **arg, char *prefix, char separator, int fd)
{
	char	c;
	int		i;
	
	if (arg)
	{
		if (prefix && *prefix)
			c = DQ;
		else
			c = 0;
		i = 0;
		while (arg[i])
		{
			if (!arg[i + 1])
				separator = 0;
			ft_putstr_fd(prefix, fd);
			ft_putchar_fd(c, fd);
			ft_putstr_fd(arg[i++], fd);
			ft_putchar_fd(c, fd);
			ft_putchar_fd(separator, fd);
		}
	}
}
