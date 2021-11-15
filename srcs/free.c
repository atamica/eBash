#include "minishell.h"

void	free_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free (*ptr);
		*ptr = NULL;
	}
}

/* void	free_nu(void *ptr)
{
	if (ptr)
		free (ptr);
} */

void	free2(char **ptr)
{
	void	**tmp;

	if (ptr)
	{
		tmp = (void **)ptr;
		while (*tmp)
		{
			free(*tmp);
			tmp++;
		}
		free((void **)ptr);
	}
}

void	close_f(int fd)
{
	if (fd > 2)
		close(fd);
}

void	free_d(t_d *d)
{
	if (d->input)
	{
//		free_null((void **)&d->cmd.path);
//		free2(d->cmd.arg);
		free_null((void **)&d->input);
//		free2(d->env_ex);
		free(d->prompt);
		free(d->path);
		free(d->input);
		d->fr = 0;	
	}
}

void	free_cmd(t_cmd *cmd)
{
	free2(cmd->arg);
	free (cmd->path);
	free (cmd->here_stop);
}