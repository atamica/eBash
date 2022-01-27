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
#ifdef NDEBUG_RUN
printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
printf("~~~~~~~~cod ret (%3d)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", run(&d));
#endif
		cmds = pa2(&d);
		if (cmds->cod == SUCCSESS)
		{
			i = -1;
			d.stat = 0;
			while ((++i < cmds->count) && !d.stat)
			{
				if (i < cmds->pipes_count)
					if_err_exit(pipe(cmds->fdp[i]), 3, &d);					
				if (cmds->pipes_count && (i > 0))
					pip_in = cmds->fdp[i - 1];	
				else
					pip_in = NULL;
				if (cmds->pipes_count && i < cmds->pipes_count)
					pip_out = cmds->fdp[i];
				else
					pip_out = NULL;
				if (cmds->cmd[i].type == EXTERNALS)		
					d.stat = cmd_cmd(&d, cmds->cmd + i, pip_in, pip_out) % 256;
				else if (cmds->cmd[i].type == BUILTINS)
				{
					d.stat = run_builtins_cmd(&d, cmds->cmd + i, pip_out) % 256;
					close_files_rd(cmds->cmd + i);
				}
#ifdef NDEBUG
				check_opened_fd();
#endif
			}
/* 			if (i > 2)
				close_f2(cmds->fdp[i]); */
			free_cmds(cmds);
			free(d.input);
		}
		else
			err_msg(msg_error(8), 0, &d);
#ifdef NDEBUG
		check_opened_fd();
#endif
	}
	printf(N);
	free_d(&d);
	return (0);
}
