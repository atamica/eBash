#include "minishell.h"
//extern int code_event;

void	init_cmd0(t_cmd *cmd)
{
	cmd->arg = NULL;
	cmd->path = NULL;
	cmd->here_stop = NULL;
	cmd->type = EMPTY;
	cmd->fds[0] = STDIN_FILENO;
	cmd->fds[1] = STDOUT_FILENO;
	cmd->code_ret = 0;
	cmd->code_red = 0;
	cmd->redir.code_in = 0;
	cmd->redir.code_out = 0;
//	cmd->env = NULL;
	cmd->fd[0] = STDIN_FILENO;
	cmd->fd[1] = STDOUT_FILENO;
	cmd->pipe = 0;
}

void	init_cmd_free(t_cmd *cmd)
{
	free_cmd(cmd);
	init_cmd0(cmd);
}

void	init_fl(t_fl *fl)
{
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
	init_cmd0(&d->cmd);
	d->ac = ac;
	d->av = av;
	d->env_ex = env;
	copy_envs(d);
	using_history ();
	tmp = getenv(LVL);
	if (tmp && ft_strlen(tmp))
		lvl = ft_atoi(tmp) + 1;
	else
		lvl = 1;
	tmp = ft_itoa(lvl);
	set_env_val(LVL, tmp, d);
	free(tmp);
	code_event = 0;
	rl_catch_signals = 0;
	init_signals();
}
