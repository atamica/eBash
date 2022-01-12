#include "minishell.h"

int	main(int ac, char **av, char **env)
{

	int		status = 1;
	t_d		d;
	t_cmds	*cmds;
	int		i;

	init_start(&d, ac, av, env);
	while (status)
	{
		d.input = readline(prompt(&d));
		free(d.prompt);
		d.fr = 1;
		if (!d.input)
		{
			status = 0;
			break ;
		}
		add_history(d.input);
/* printf("###################################################\n");
run(d.input);
printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");	 */	
		cmds = pa2(&d);
		i = -1;
		while (++i < cmds->count)
			printf("%2i. str(%s) type(%i)\n", i, cmds->cmd[i].path,  cmds->cmd[i].type);
		printf("===================================================\n");
		i = -1;
		d.stat = 0;
		while ((++i < cmds->count) && !d.stat)
		{
			if (i < cmds->count)
				if_err_exit(pipe(cmds->cmd[i].fd), 3, &d);
			if (cmds->cmd[i].type == EXTERNALS)
				d.stat = cmd_cmd(&d, cmds->cmd + i);
			else if (cmds->cmd[i].type == BUILTINS)
				d.stat = run_builtins_cmd(&d, cmds->cmd + i);
			printf("~~~~~~~~~~~~~~~~~~~~ code_ret(%i)\n", d.stat);
		}
		free_cmds(cmds);
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		init_cmd_free(&d.cmd);
		free(d.input);
		close_f2(d.cmd.fd);
	}
	printf(N);
	free_d(&d);
	return (0);
}
