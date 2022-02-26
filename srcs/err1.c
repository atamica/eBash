#include "minishell.h"

int	out_msg(char *msg, int code)
{
	perror(msg);
	return (code);
}

void	if_err_fatal(void *ptr, int code, t_d *d)
{
	if (!ptr)
		err(code, d);
}

int	syntax_err(char c)
{
	printf("%s: %s «%c»\n", PRMT, MSGE13, c);
	return (2);
}

int	err_open(int fd, t_d *d)
{
	if (fd < 0)
	{
		err_msg(MSGE4, 0, d);
		return (ERROR);
	}
	return (SUCCSESS);
}

void	if_err_cd(int er, int fd, char *path)
{
	if (er < 0)
	{
		ft_putstr_fd(CD, fd);
		if (path)
			ft_putstr_fd(path, fd);
		ft_putendl_fd(": Нет такого файла или каталога", fd);
	}
}
