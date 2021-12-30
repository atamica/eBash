/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 08:22:25 by atamica           #+#    #+#             */
/*   Updated: 2021/11/07 08:22:34 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	fl;

	fl = (cmd->arg && !ft_strncmp(*(cmd->arg + 1), "-n", 3));
	print_param_fd(cmd->arg + fl + 1, MSG0, ' ', STDOUT_FILENO);	//fd => cmd->fd[1]
	if (!fl)
		printf(N);
	return (0);
}
