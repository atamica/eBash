#include "minishell.h"

int	ft_export(t_d *d, t_fout fout)
{
	print_param_fd(d->env, "declare -x ", '\n', fout.fd);
	if (fout.fl_close)
		close_f(fout.fd);
	return (0);
}
