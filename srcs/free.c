#include "minishell.h"

void	free_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free (*ptr);
		*ptr = NULL;
	}
}

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

void	free_d(t_d *d)
{
	if (d->input)
	{
		free_null((void **)&d->input);
		free(d->input);
		free2(d->env);
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		free2(cmd->arg);
		free (cmd->path);
		free (cmd->here_stop);
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
