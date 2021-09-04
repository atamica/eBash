#include "minishell.h"

void	free_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free (*ptr);
		*ptr = NULL;
	}
}

void	free_nu(void *ptr)
{
	if (ptr)
		free (ptr);
}

void	free2(char **ptr)
{
	void	**tmp;

	if (ptr)
	{
		tmp = (void **)ptr;
		while (*tmp)
			free_nu(*tmp++);
		free_nu(ptr);
	}
}

void	close_f(int fd)
{
	if (fd > 2)
		close(fd);
}

void	free_d(t_d *d)
{
	if (d->fr)
	{
		close_f(d->file1.fd);
		close_f(d->file2.fd);
		free_nu(d->pipe_fd);
		free_nu(d->cmd1.path);
		free2(d->cmd1.arg);
		free_nu(d->cmd2.path);
		free2(d->cmd2.arg);
		d->fr = 0;
	}
}
