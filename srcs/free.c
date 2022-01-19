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
	char	**tmp;

	if (ptr)
	{
		tmp = ptr;
		while (*tmp)
		{
			free(*tmp);
			tmp++;
		}
		free(ptr);
	}
}

void	close_f(int fd)
{
	if (fd > 2)
		close(fd);
}

void	close_f2(int *fd)
{
	if (fd[IN] > 2)
			close(fd[IN]);
	if (fd[OUT] > 2)
		close(fd[OUT]);
}

void	close_f3(int *fd)
{
	close_f(fd[0]);
	close_f(fd[1]);
	close_f(fd[2]);
}

void	free_d(t_d *d)
{
	if (d->input)
	{
		free_null((void **)&d->input);
//		free(d->prompt);
		free(d->path);
		free(d->input);
		free2(d->env);
		d->fr = 0;
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		free2(cmd->arg);
		free (cmd->path);
		free (cmd->here_stop);
		free (cmd->str);
	}
}

void	free_cmds(t_cmds *cmds)
{
	int		i;
	t_cmd	*tmp;

	if (cmds)
	{
		tmp = cmds->cmd;
		while (cmds->count--)
			free_cmd(tmp++);
		i = -1;
		while (++i < cmds->pipes_count)
			free(cmds->fdp[i]);
		free(cmds->fdp);
		free(cmds->cmd);
		free(cmds);
	}
}