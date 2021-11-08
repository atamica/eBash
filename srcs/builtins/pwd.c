/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 09:50:58 by atamica           #+#    #+#             */
/*   Updated: 2021/11/07 09:51:01 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*tmp;

	tmp = malloc(LEN_PATH);
	if (tmp)
	{
		printf("%s\n", getcwd(tmp, LEN_PATH));
		free(tmp);
		return (0);
	}
	return (2);
}
