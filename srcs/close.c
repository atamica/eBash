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
