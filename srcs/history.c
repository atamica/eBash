#include "minishell.h"

int	add_to_hist_file(const char *f_name)
{	
	int		fd;
	char	*cmd_line;

	cmd_line = NULL;
	fd = open(f_name, FILE_APPEND, FILE_PERM);
	while (get_next_line(fd, &cmd_line))
	{
		add_history(cmd_line);
		free(cmd_line);
		cmd_line = NULL;
	}
	return (fd);
}

/* char	*n_cmd_from_history(size_t n, int fd, t_d *d)
{
	char	*res;

	//
	res = NULL;
	
	return (res);
} */