#include "minishell.h"

void	h_doc(int fd, t_cmd *cmd, t_d *d)
{
	int		i;
	char	*line;
	size_t	len;

	if (cmd->here_stop)
	{
		len = ft_strlen(cmd->here_stop);
		i = get_next_line(cmd->fd[0], &line);
		while (i)
		{
			if_err_exit(i, 9, d);
			if (!ft_strncmp(cmd->here_stop, line, len))
			{
				printf("H_STOP!\n");
				break ;
			}
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