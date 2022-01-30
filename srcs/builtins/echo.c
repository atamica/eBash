#include "minishell.h"

int	ft_echo(t_cmd *cmd, int fd)
{
	int		fl;
	char	**ptr;

print_param(cmd->arg, ">-<", '|');
	fl = (cmd->arg[1] && !ft_strncmp(cmd->arg[1], "-n", 3));
printf("| fl=%i\n", fl);	
	ptr = cmd->arg + fl + 1;
	while (ptr && *ptr)
	{
		ft_putstr_fd(*ptr, fd);
		if (*++ptr)
			ft_putchar_fd(SP, fd);
	}
	if (!fl)
		ft_putchar_fd(*N, fd);
	return (0);
}
