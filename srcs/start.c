/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:46:30 by atamica           #+#    #+#             */
/*   Updated: 2022/01/20 21:46:35 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_d		d;
	t_cmds	*cmds;
	int		i;

	init_start(&d, ac, av, env);
	while (1)
	{
		d.input = readline(prompt(&d));
		free(d.prompt);
		d.fr = 1;
		if (!d.input)
			break ;
		if (!ft_isalsp(*d.input))
			add_history(d.input);
//printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//printf("~~~~~~~~cod ret (%3d)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", run(&d));
		cmds = pa2(&d);
		i = -1;
		while (++i < cmds->count)
			printf("%2i. str(%s) type(%i)\n", i, cmds->cmd[i].path,  \
			cmds->cmd[i].type);
		printf("===================================================\n");
		i = -1;
		d.stat = 0;
		while ((++i < cmds->count) && !d.stat)
		{
			if (i < cmds->pipes_count)
			{
				if_err_exit(pipe(cmds->fdp[i]), 3, &d);
				// check if > or >> for out
				//			< or << for in
			}
			if (cmds->cmd[i].type == EXTERNALS)
				d.stat = cmd_cmd(&d, cmds->cmd + i, \
				(i > 0  && cmds->pipes_count) ? cmds->fdp[i - 1] : NULL, \
				(i < cmds->pipes_count && cmds->pipes_count) ? cmds->fdp[i] : NULL);
			else if (cmds->cmd[i].type == BUILTINS)
				d.stat = run_builtins_cmd(&d, cmds->cmd + i);
			printf("~~~~~~~~~~~~~~ code_ret(%3i) ~~~~~\n", d.stat);
		}
		free_cmds(cmds);
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		free(d.input);
		close_f3(d.cmd.fd);
	}
	printf(N);
	free_d(&d);
	return (0);
}
