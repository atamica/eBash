/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 22:52:43 by atamica           #+#    #+#             */
/*   Updated: 2021/11/06 22:52:54 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pth(char *ptr)
{
	char	*tmp;
	char	*path;

	path = NULL;
	tmp = malloc(LEN_PATH);
	if (!tmp)
		return (tmp);
	path = ft_strjoin_m(getcwd(tmp, LEN_PATH), ptr);
	free(tmp);
	return (path);
}

int	ft_cd(t_cmd *cmd)
{
	char	*path;
	int		res;

	path = NULL;
	if (cmd->arg && cmd->arg[1] && cmd->arg[2])
	{
		printf("%s: cd: слишком много аргументов\n", PRMT);
		return (1);
	}
	if (cmd->arg && cmd->arg[1])
	{
		if (cmd->arg[1][0] == SL)
			path = ft_strdup(cmd->arg[1]);
		else
			path = pth(cmd->arg[1]);
		if (!path)
			return (2);
	}
	if (cmd->arg && !cmd->arg[1])
		path = ft_strdup(getenv("HOME"));
	res = chdir(path);
	if (res < 0)
		printf("%s: cd: %s: Нет такого файла или каталога\n", PRMT, path);
	free(path);
	return (-res);
}
