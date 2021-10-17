
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

#define FILE_PERM 0664

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

int main(void)
{
	char *cmd_line;
	int fd;
	
	fd = add_to_hist_file("minishell_hist");
	while (1)
	{
		cmd_line = readline("minish:\\");
		add_history(cmd_line);
		write(fd, cmd_line, ft_strlen(cmd_line));
		write(fd, "\n", 1);
	}
	return (0);
}
