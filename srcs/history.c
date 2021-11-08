#include "minishell.h"

int add_to_hist_file(const char *f_name)
{	
	char *cmd_line;
	int fd;

	cmd_line = NULL;
	fd = open(f_name, O_RDWR | O_CREAT | O_APPEND, FILE_PERM);
	while (get_next_line(fd, &cmd_line))
	{
		add_history(cmd_line);
	}
	if (cmd_line)
		add_history(cmd_line);
	return (fd);
}