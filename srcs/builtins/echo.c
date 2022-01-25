#include "minishell.h"

int	ft_echo(t_cmd *cmd, t_fout fout)
{
	int		fl;
	char	**ptr;

	fl = (cmd->arg && !ft_strncmp(*(cmd->arg + 1), "-n", 3));
	ptr = cmd->arg + fl + 1;
	while (*ptr)
	{
		ft_putstr_fd(*ptr, fout.fd);
		if (*++ptr)
			ft_putchar_fd(SP, fout.fd);
	}
	if (!fl)
		ft_putchar_fd('\n', fout.fd);
 	if (fout.fl_close)
		close_f(fout.fd);
	return (0);
}
