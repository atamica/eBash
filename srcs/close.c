#include "minishell.h"

void	close_f(int fd)
{
	if (fd > 2)
		close(fd);
}

void	close_f2(int *fd)
{
	if (fd)
	{
		if (fd[IN] > 2)
				close(fd[IN]);
		if (fd[OUT] > 2)
			close(fd[OUT]);
	}
}

void	close_f3(int *fd)
{
	if (fd)
	{
		close_f(fd[0]);
		close_f(fd[1]);
		close_f(fd[2]);
	}
}

void	close_f3any(int *fd)
{
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
		close(fd[2]);
	}
	
}
void	close_f2any(int *fd)
{
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

void	close_files_rd(t_cmd *cmd)
{
	if (cmd->code_red > 0)
	{
		if ((cmd->code_red & S_LEFT) || (cmd->code_red & D_LEFT))
			close_f(cmd->fd[0]);		// _f	?
		if ((cmd->code_red & S_RIGHT) || (cmd->code_red & D_RIGHT))
			close_f(cmd->fd[1]);		// _f
	}
}

void	close_if(t_fout fout)
{
	if (fout.fl_close)
		close_f(fout.fd);
}