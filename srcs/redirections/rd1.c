/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:55:12 by atamica           #+#    #+#             */
/*   Updated: 2021/11/07 12:55:17 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rd_s_left(char *str, t_cmd *cmd, t_d *d)
{
	char	*ptr;
	char	*tmp;

	ptr = get_pos_char(str, L) + 1;
	tmp = filename(ptr);
	if (tmp)
	{
		cmd->fd[0] = open(tmp, O_RDONLY, 0777);
		free(tmp);
		if (err_open(cmd->fd[0], d))
			return (ERROR);
	}
	return (SUCCSESS);
}

int	rd_d_left(char *str, t_cmd *cmd)
{
	char	*ptr;

	ptr = get_pos_char(str, L) + 2;
	cmd->here_stop = filename(ptr);
	if (!ft_strlen(cmd->here_stop))
		return (ERROR);
	return (SUCCSESS);
}

int	rd_s_right(char *str, t_cmd *cmd, t_d *d)
{
	char	*ptr;
	char	*tmp;

	ptr = get_pos_char(str, R) + 1;
	tmp = filename(ptr);
	if (tmp)
	{
		cmd->fd[1] = open(tmp, O_RDWR, 0777);
		free (tmp);
		if (err_open(cmd->fd[1], d))
			return (ERROR);
	}
	return (SUCCSESS);
}

int	rd_d_right(char *str, t_cmd *cmd, t_d *d)
{
	char	*ptr;
	char	*tmp;

	ptr = get_pos_char(str, R) + 2;
	tmp = filename(ptr);
	if (tmp)
	{
		cmd->fd[1] = open(tmp, O_APPEND | O_RDWR | O_CREAT, 0777);
		free (tmp);
		if (err_open(cmd->fd[1], d))
			return (ERROR);
	}
	return (SUCCSESS);
}

int	get_fd(char *str, t_d *d, t_cmd *cmd)
{
	*(cmd->fd) = STDIN_FILENO;
	*(cmd->fd + 1) = STDOUT_FILENO;
	cmd->code_red = find_redir(str);
	if (cmd->code_red < 0)
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
