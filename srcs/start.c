#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_d		d;
	t_cmds	*cmds;
	int		i;
	int		*pip_in;
	int		*pip_out;

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
/*
#ifdef NDEBUG
printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
printf("~~~~~~~~cod ret (%3d)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", run(&d));
#endif
*/
		cmds = pa2(&d);
#ifdef NDEBUG
		i = -1;
		while (++i < cmds->count)
			printf("%2i. str(%s) type(%i)\n", i, cmds->cmd[i].path,  \
			cmds->cmd[i].type);
		printf("===================================================\n");
#endif
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
			{
				if (i > 0  && cmds->pipes_count)
					pip_in = cmds->fdp[i - 1];	
				else
					pip_in = NULL;
				if (i < cmds->pipes_count && cmds->pipes_count)
					pip_out = cmds->fdp[i];
				else
					pip_out = NULL;
				d.stat = cmd_cmd(&d, cmds->cmd + i, pip_in, pip_out);
			}
			else if (cmds->cmd[i].type == BUILTINS)
				d.stat = run_builtins_cmd(&d, cmds->cmd + i);
#ifdef NDEBUG
			printf("~~~~~~~~~~~~~~ code_ret(%3i) ~~~~~\n", d.stat);
#endif
		}
		free_cmds(cmds);
#ifdef NDEBUG
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
#endif
		free(d.input);
		close_f3(d.cmd.fd);
	}
	printf(N);
	free_d(&d);
	return (0);
}
