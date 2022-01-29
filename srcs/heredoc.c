#include "minishell.h"

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
			if (cmd->fl_replace_dl)
				line = repl_dlr(line, d);
			ft_putendl_fd(line, fd);
			free(line);
			i = get_next_line(cmd->fd[0], &line);
		}
		free(line);
//		close_f(fd);
	}
}

void	prepare_hdoc(t_cmd *cmd, t_d *d)
{
	int		pipe_hd[2];
	int		stat;
	pid_t	pid_hd;


	if_err_exit(pipe(pipe_hd), 3, d);
	if_err_exit(pid_hd = fork(), 5, d);
	if (!pid_hd)
	{
		close_f(pipe_hd[0]);
		h_doc(pipe_hd[1], cmd, d);
		close_f(pipe_hd[1]);
		free_cmd(cmd);
		free_d(d);
		exit(0);
	}
	dup2(pipe_hd[0], IN);
	close_f2(pipe_hd);
	if_err_exit(waitpid(pid_hd, &stat, 0), 7, d);
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