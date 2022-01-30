#include "minishell.h"

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

char	*skip_spaces(char *ptr)
{
	if (ptr)
	{
		while (*ptr && ft_isalsp(*ptr))
			ptr++;
	}
	return (ptr);
}

char	*skip_not_spaces(char *ptr)
{
	if (ptr)
	{
		while (*ptr && !ft_isalsp(*ptr))
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
	
	if (arg)
	{
		c = (prefix && *prefix) * DQ;
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
