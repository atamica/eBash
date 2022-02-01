#include "minishell.h"

static	void	replace_h(char **line, char **env)
{
	char	*tmp;

	tmp = *line;
	*line = repl_dlr(*line, env, 0);
	if (tmp != *line)
		free (tmp);
}

void	h_doc(int fd, t_cmd *cmd, t_d *d)
{
	int		i;
	char	*line;
	size_t	len;

	if (cmd->here_stop)
	{
		len = ft_strlen(cmd->here_stop) + 1;
		i = get_next_line(cmd->fd[0], &line);
		while (i)
		{
			if_err_exit(i, 9, d);
			if (!ft_strncmp(cmd->here_stop, line, len))
				break ;
			if (cmd->fl_replace)
				replace_h(&line, d->env);
			ft_putendl_fd(line, fd);
			free(line);
			i = get_next_line(cmd->fd[0], &line);
		}
		free(line);
	}
}

void	prepare_hdoc_pipe(t_cmd *cmd, t_d *d, int *pipe_in)
{
	int		pipe_hd[2];

	if_err_exit(pipe(pipe_hd), 3, d);
	h_doc(pipe_hd[1], cmd, d);
	if (pipe_in)
		if_err_exit(dup2(pipe_hd[1], pipe_in[0]), 6, d);
	else
		if_err_exit(dup2(pipe_hd[0], IN), 6, d);
	close_f2(pipe_hd);
}
