#include "minishell.h"

static size_t	add_str(char *ptr, char *str, size_t offset)
{
	size_t	len;

	len = ft_strlen(str);
	ft_memcpy(ptr + offset, str, len);
	return (len);
}

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
	if_err_fatal(d->prompt = (char *)malloc(len), 2, d);
	len = add_str(d->prompt, GREEN, 0);
	len += add_str(d->prompt, user, len);
	free(user);
	len += add_str(d->prompt, RESET, len);
	*(d->prompt + len++) = ':';
	len += add_str(d->prompt, BLUE, len);
	len += add_str(d->prompt, path, len);
	len += add_str(d->prompt, RESET, len);
	ft_memcpy(d->prompt + len, "$", 2);
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
			c = DQ;
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
//	int		i;
	
	if (arg)
	{
		c = (prefix && *prefix) * DQ;
//		i = 0;
		while (*arg)
		{
			ft_putstr_fd(prefix, fd);
			ft_putchar_fd(c, fd);
			ft_putstr_fd(*arg, fd);
			ft_putchar_fd(c, fd);
			if (*(++arg))
				ft_putchar_fd(separator, fd);
		}
	}
}
