#include "minishell.h"
//extern int code_event;

void	init_cmd(t_cmd *cmd)
{
	cmd->arg = NULL;
	cmd->path = NULL;
	cmd->str = NULL;
	cmd->here_stop = NULL;
	cmd->type = EMPTY;
//	cmd->fds[0] = IN;
//	cmd->fds[1] = OUT;
	cmd->code_ret = 0;
	cmd->code_red = 0;
	cmd->redir.code_in = 0;
	cmd->redir.code_out = 0;
	cmd->env = NULL;
//	cmd->fd = {IN, OUT, ER};
 	cmd->fd[0] = IN;
	cmd->fd[1] = OUT;
	cmd->fd[2] = ER;
//	cmd->std_io = (t_io){.in = dup(IN), .out = dup(OUT), .err = dup(ER)};
	// check err in dup
	cmd->pipe = 0;
}

void	init_fl(t_fl *fl)
{
	// *fl = (t_fl){0, 0, 0, 0, 0};
	fl->fl_s_qu = 0;
	fl->fl_d_qu = 0;
	fl->fl_dol = 0;
	fl->fl_op_bkt = 0;
	fl->fl_cl_bkt = 0;
}

void	init_start(t_d *d, int ac, char **av, char **env)
{
	int		lvl;
	char	*tmp;

# if OS == LINUX
	rl_clear_history();
# endif
	init_cmd(&d->cmd);

	d->ac = ac;
	d->av = av;
	copy_envs(env, d);
	using_history ();
	tmp = get_env_val(d->env, LVL);
	if (tmp && ft_strlen(tmp))
		lvl = ft_atoi(tmp) + 1;
	else
		lvl = 1;
	free(tmp);
	tmp = ft_itoa(lvl);
	set_env_val(LVL, tmp, d);
	free(tmp);
	code_event = 0;
	rl_catch_signals = 0;
	init_signals();
}
