#include "minishell.h"

void	my_handler(int signo)
{
	if (signo == SIGINT)	// Ctrl+C
	{
		ft_putendl_fd(CC, ER);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signals(t_d *d)
{
	if (signal(SIGINT, my_handler) == SIG_ERR)
		err(14, d);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		err(14, d);
}
