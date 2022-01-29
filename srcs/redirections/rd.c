#include "minishell.h"

static void	s_redir(char *ptr, char c, int *r, int code_redir)
{
	if ((*r != -1) && ptr && *ptr && (ptr[1] != c))
	{
		if (get_pos_char(ptr + 1, c))
			*r = ERROR;
		else
			*r |= code_redir;
	}
}

static void	d_redir(char *ptr, char c, int *r, int code_redir)
{
	if ((*r != -1) && ptr && *ptr && (ptr[1] == c))
	{
		if (get_pos_char(ptr + 2, c))
			*r = ERROR;
		else
			*r |= code_redir;
	}
}

int	find_redir(char *str)
{
	char	*tmp;
	int		res;

	res = NONE;
	if (str)
	{
		tmp = get_pos_char(str, L);
		s_redir(tmp, L, &res, S_LEFT);
		d_redir(tmp, L, &res, D_LEFT);
		tmp = get_pos_char(str, R);
		s_redir(tmp, R, &res, S_RIGHT);
		d_redir(tmp, R, &res, D_RIGHT);
	}
	return (res);
}

char	*filename(char *ptr)
{
	char	*st;
	char	*st_del;
	char	*res;
	size_t	len_file_name;

	res = NULL;
	if (ptr)
	{
		st_del = ptr;
		ptr = skip_spa(ptr);
		st = ptr;
		while (*ptr && !ft_isalsp(*ptr))
			ptr++;
		len_file_name = ptr - st;
		if (len_file_name)
		{
			res = ft_substr(st, 0, len_file_name);
			del_substring(st_del, ptr - st_del);
		}
	}
	return (res);
}

void	restore_std_io(t_d *d)
{
	if_err_exit(dup2(d->std_fd[0], IN), 3, d);
	if_err_exit(dup2(d->std_fd[1], OUT), 3, d);
	if_err_exit(dup2(d->std_fd[2], ER), 3, d);
}