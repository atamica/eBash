#include "minishell.h"

int	rd_s_left(char *str, t_cmd *cmd, t_d *d)
{
	char	*ptr;
	char	*fname;

	ptr = get_pos_char(str, L);
	del_substring(ptr, 1);
	fname = filename(ptr);
	ptr = strip_quo(fname, cmd->env, (fname != ptr));
	if (ptr)
		cmd->fd[0] = open(ptr, O_RDONLY);
	free(ptr);
	return (!ptr || err_open(cmd->fd[0], d));
}

int	rd_d_left(char *str, t_cmd *cmd)
{
	char	*ptr;
	char	*hstop;

	del_substring(ptr = get_pos_char(str, L), 2);
	hstop = filename(ptr);
	if (hstop && is_in_quo(hstop))
	{
		cmd->fl_replace = 1;
		del_quo(hstop, *hstop);
	}
	cmd->here_stop = hstop;
	return (!cmd->here_stop);
}

int	rd_s_right(char *str, t_cmd *cmd, t_d *d)
{
	char	*ptr;
	char	*fname;

	del_substring(ptr = get_pos_char(str, R), 1);
	fname = filename(ptr);
	ptr = strip_quo(fname, cmd->env, (ptr != fname));
	if (ptr)
		cmd->fd[1] = open(ptr, O_RDWR | O_CREAT | O_TRUNC, FILE_PERM);
	free(ptr);
	return (!ptr || err_open(cmd->fd[1], d));
}

int	rd_d_right(char *str, t_cmd *cmd, t_d *d)
{
	char	*ptr;
	char	*fname;

	del_substring(ptr = get_pos_char(str, R), 2);
	fname = filename(ptr);
	ptr = strip_quo(fname, cmd->env, (ptr != fname));
	if (ptr)
		cmd->fd[1] = open(ptr, O_RDWR | O_CREAT | O_APPEND, FILE_PERM);
	free(ptr);
	return (!ptr || err_open(cmd->fd[1], d));
}

int	get_fd(char *str, t_d *d, t_cmd *cmd)
{
	cmd->code_red = find_redir(str);
	if ((cmd->code_red < 0) || \
		((cmd->code_red & S_LEFT) && (cmd->code_red & D_LEFT)) || \
		((cmd->code_red & S_RIGHT) && (cmd->code_red & D_RIGHT)))
		return (ERROR);
	if ((cmd->code_red & S_LEFT) && rd_s_left(str, cmd, d))
		return (ERROR);
	if ((cmd->code_red & D_LEFT) && rd_d_left(str, cmd))
		return (ERROR);
	if ((cmd->code_red & S_RIGHT) && rd_s_right(str, cmd, d))
		return (ERROR);
	if ((cmd->code_red & D_RIGHT) && rd_d_right(str, cmd, d))
		return (ERROR);
	return (SUCCSESS);
}
