/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 09:36:21 by atamica           #+#    #+#             */
/*   Updated: 2021/11/07 09:37:12 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_cmd(char *cmd)
{
	if (is_builtins(cmd))
		return (BUILTINS);
	if (is_ext_cmd(cmd))
		return (EXTERNALS);
	if (!ft_strncmp(cmd, "|", 2))
		return (PIPE);
	if (!ft_strncmp(cmd, "<", 2) || !ft_strncmp(cmd, "<<", 3) || \
		!ft_strncmp(cmd, ">", 2) || !ft_strncmp(cmd, ">>", 3))
		return (REDIRECTIONS);
	if (!ft_strncmp(cmd, "||", 3))
		return (OR);
	if (!ft_strncmp(cmd, "&&", 3))
		return (AND);
	return (OTHERS);
}

int	run_builtins(t_d *d)
{
	int		res;

	res = 0;
	if (d->cmd.type == BUILTINS)
	{
		if (!ft_strncmp(d->cmd.path, "cd", 3))
			return (ft_cd(&d->cmd));
		if (!ft_strncmp(d->cmd.path, "echo", 5))
			return (ft_echo(&d->cmd));
		if (!ft_strncmp(d->cmd.path, "pwd", 4))
			return (ft_pwd());
		if (!ft_strncmp(d->cmd.path, "env", 4))
			return (ft_env(d));
		if (!ft_strncmp(d->cmd.path, "export", 7))
			return (ft_export(d));
		if (!ft_strncmp(d->cmd.path, "exit", 5))
			return (ft_exit(d));
		if (!ft_strncmp(d->cmd.path, "unset", 6))
			return (ft_unset(d->cmd.arg[1], d));
	}
	return (res);
}

int	run_builtins_cmd(t_d *d, t_cmd *cmd)
{
	int		res;

	res = 0;
	if (cmd->type == BUILTINS)
	{
		if (!ft_strncmp(cmd->path, "cd", 3))
			return (ft_cd(cmd));
		if (!ft_strncmp(cmd->path, "echo", 5))
			return (ft_echo(cmd));
		if (!ft_strncmp(cmd->path, "pwd", 4))
			return (ft_pwd());
		if (!ft_strncmp(cmd->path, "env", 4))
			return (ft_env(d));
		if (!ft_strncmp(cmd->path, "export", 7))
			return (ft_export(d));
		if (!ft_strncmp(cmd->path, "exit", 5))
			return (ft_exit(d));
		if (!ft_strncmp(cmd->path, "unset", 6))
			return (ft_unset(cmd->arg[1], d));
	}
	return (res);
}
