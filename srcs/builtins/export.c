#include "minishell.h"

int	ft_export(t_d *d, int fd)
{
	char	**ptr;
	char	*str;

	ptr = d->env;
	if (ptr)
	{
		while (*ptr)
		{
			str = ft_strchr(*ptr, '=') + 1;
			if (str)
			{
				ft_putstr_fd("declare -x ", fd);
				write(fd, *ptr, str - *ptr);
				ft_putchar_fd(DQ, fd);
				ft_putstr_fd(str, fd);
				ft_putendl_fd("\"", fd);
			}
			ptr++;
		}
	}
	return (0);
}
