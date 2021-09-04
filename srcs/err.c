#include "minishell.h"

void	err_msg(char *msg, int code, t_d *d)
{
	write(2, msg, ft_strlen(msg));
	if (code > 1)
		free_d(d);
	if (code)
		exit(code);
}

void	err(int code, t_d *d)
{
	if (code == 1)
		err_msg(MSGE1, code, d);
	if (code == 2)
		err_msg(MSGE2, code, d);
	if (code == 3)
		err_msg(MSGE3, code, d);
	if (code == 4)
		err_msg(MSGE4, code, d);
	if (code == 5)
		err_msg(MSGE5, code, d);
	if (code == 6)
		err_msg(MSGE6, code, d);
	if (code == 7)
		err_msg(MSGE7, code, d);
	if (code == 8)
		err_msg(MSGE8, code, d);
	if (code == 9)
		err_msg(MSGE9, code, d);
}

void	if_err_exit(int er, int code, t_d *d)
{
	if (er < 0)
		err(code, d);
}

int	out_msg(char *msg, int code)
{
	perror(msg);
	return (code);
}