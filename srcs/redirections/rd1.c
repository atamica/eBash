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

	del_substring(ptr = get_pos_char(str, L), 1);
	tmp = filename(ptr);
	if (tmp)
	{
		cmd->fd[0] = open(tmp, O_RDONLY);
		free(tmp);
	}
	return (!tmp || err_open(cmd->fd[0], d));
}

int	rd_d_left(char *str, t_cmd *cmd)
{
	char	*ptr;

	del_substring(ptr = get_pos_char(str, L), 2);
	return (!(cmd->here_stop = filename(ptr)));
}

int	rd_s_right(char *str, t_cmd *cmd, t_d *d)
{
	char	*ptr;
	char	*tmp;

	del_substring(ptr = get_pos_char(str, R), 1);
	tmp = filename(ptr);
	if (tmp)
	{
		cmd->fd[1] = open(tmp, O_RDWR | O_CREAT | O_TRUNC, FILE_PERM);
printf("rd_s_r %i\n", cmd->fd[1]);
		free (tmp);
	}
	return (!tmp || err_open(cmd->fd[1], d));//(cmd->fd[1] < 0)
}

int	rd_d_right(char *str, t_cmd *cmd, t_d *d)
{
	char	*ptr;
	char	*tmp;

	del_substring(ptr = get_pos_char(str, R), 2);
	tmp = filename(ptr);
	if (tmp)
	{
		cmd->fd[1] = open(tmp, O_APPEND | O_RDWR | O_CREAT, FILE_PERM);
		free (tmp);
	}
	return (!tmp || err_open(cmd->fd[1], d));
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
