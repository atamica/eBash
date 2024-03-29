#include "minishell.h"

/*
**	function insert char between s1 and s2
**	retunrn new str or NULL
*/

char	*ft_strjoin_c(char const *s1, char const *s2, char c)
{
	char	*r;
	size_t	l1;
	size_t	l2;
	int		size_c;

	r = NULL;
	if (s1 && s2)
	{
		size_c = (c != 0);
		l1 = ft_strlen(s1);
		l2 = ft_strlen(s2);
		r = (char *)malloc((l1 + l2 + 1 + size_c) * sizeof(char));
		if (r)
		{
			ft_strlcpy(r, s1, l1 + 1);
			*(r + l1) = c;
			ft_strlcpy(r + l1 + size_c, s2, l2 + 1);
		}
	}
	return (r);
}

char	*add_path(char *cmd)
{
	char	*cmd_path;
	char	**paths;
	char	**tmp;

	paths = ft_split(getenv("PATH"), ':');
	cmd_path = NULL;
	if (paths)
	{
		tmp = paths;
		while (*tmp && !cmd_path)
		{
			cmd_path = ft_strjoin_c(*tmp++, cmd, SL);
			if (is_file_exist(cmd_path) != 1)
				free_null((void **)&cmd_path);
		}
		free2(paths);
	}
	if (!cmd_path && (is_file_exist(cmd) == 1))
		cmd_path = ft_strdup(cmd);
	return (cmd_path);
}

void	dup2_check(int old_fd, int new_fd, t_d *d)
{
	if (new_fd != old_fd)
	{
		if (dup2(old_fd, new_fd) != new_fd)
			err(6, d);
		close(old_fd);
	}
}

void	dup_io(int *fd, t_d *d, int *pipe_in, int *pipe_out)
{
	if (fd)
	{
		if ((fd[0] == IN) && pipe_in)
		{
			dup2_check(pipe_in[0], IN, d);
			close(pipe_in[1]);
		}
		else
		{
			dup2_check(fd[0], IN, d);
			close_f2any(pipe_in);
		}
		if ((fd[1] == OUT) && pipe_out)
		{
			dup2_check(pipe_out[1], OUT, d);
			close(pipe_out[0]);
		}
		else
		{
			dup2_check(fd[1], OUT, d);
			close_f2any(pipe_out);
		}
		dup2_check(fd[2], ER, d);
	}
}
