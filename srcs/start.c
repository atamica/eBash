#include "minishell.h"

static	int	input(t_d *d)
{
	d->input = readline(prompt(d));
	free(d->prompt);
	if (!d->input)
		return (0);
	if (!ft_isalsp(*d->input))
		add_history(d->input);
	return (1);
}

static	void	run_builtin(int i, int *pip_out, t_cmds *cmds, t_d *d)
{
	d->stat = run_builtins_cmd(d, cmds->cmd + i, pip_out) % 256;
	close_files_rd(cmds->cmd + i);
}

static	void	run_cmd(t_cmds *cmds, t_d *d)
{
	int		*pip_in;
	int		*pip_out;
	int		i;

	i = -1;
	d->stat = 0;
	while ((++i < cmds->count) && !d->stat)
	{
		if (i < cmds->pipes_count)
			if_err_exit(pipe(cmds->fdp[i]), 3, d);
		if (cmds->pipes_count && (i > 0))
			pip_in = cmds->fdp[i - 1];
		else
			pip_in = NULL;
		if (cmds->pipes_count && i < cmds->pipes_count)
			pip_out = cmds->fdp[i];
		else
			pip_out = NULL;
		if (cmds->cmd[i].type == EXTERNALS)
			d->stat = cmd_cmd(d, cmds->cmd + i, pip_in, pip_out) % 256;
		else if (cmds->cmd[i].type == BUILTINS)
			run_builtin(i, pip_out, cmds, d);
	}
}

int	main(int ac, char **av, char **env)
{
	t_d		d;
	t_cmds	*cmds;

	init_start(&d, ac, av, env);
	while (input(&d))
	{
		cmds = pa2(&d);
		if (cmds->cod == SUCCSESS)
		{
			run_cmd(cmds, &d);
			free_cmds(cmds);
			free(d.input);
			restore_std_io(&d);
		}
		else
			err_msg(msg_error(8), 0, &d);
	}
	restore_std_io(&d);
	printf(N);
	free_d(&d);
	return (0);
}
