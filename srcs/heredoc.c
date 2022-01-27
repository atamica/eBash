#include "minishell.h"

void	h_doc(int fd, t_cmd *cmd, t_d *d)
{
	int		fl_interpreter;
	int		i;
	char	*line;
	size_t	len;

	fl_interpreter = 1;
	if (cmd->here_stop)
	{
		if (*cmd->here_stop == SQ || *cmd->here_stop == DQ)
		{
			cmd->here_stop = replace_q(cmd->here_stop, *cmd->here_stop);
			fl_interpreter = 0;
		}
		len = ft_strlen(cmd->here_stop);
		i = get_next_line(cmd->fd[0], &line);
		while (i)
		{
			// err handler
			if_err_exit(i, 9, d);
			
			// output line  to fd
			if (!ft_strncmp(cmd->here_stop, line, len))
				break ;
			if (fl_interpreter)
			line = repl_dlr(line,d);
			ft_putendl_fd(line, fd);
			free(line);
			i = get_next_line(cmd->fd[0], &line);
		}
		free(line);
//		close_f(fd);
	}
}