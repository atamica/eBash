#include "minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->arg = NULL;
	cmd->path = NULL;
	cmd->ac = 0;
	cmd->here_stop = NULL;
	cmd->type = EMPTY;
	cmd->code_ret = 0;
	cmd->code_red = 0;
	cmd->env = NULL;
	cmd->fd[0] = IN;
	cmd->fd[1] = OUT;
	cmd->fd[2] = ER;
	cmd->fl_replace = 0;
}

#if OS == LINUX

void	init_start(t_d *d, int ac, char **av, char **env)
{
	int		lvl;
	char	*tmp;

	rl_clear_history();
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
	rl_catch_signals = 0;
	init_signals(d);
	d->std_fd[0] = dup(IN);
	d->std_fd[1] = dup(OUT);
	d->std_fd[2] = dup(ER);
}

#else

void	init_start(t_d *d, int ac, char **av, char **env)
{
	int		lvl;
	char	*tmp;

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
	rl_catch_signals = 0;
	init_signals(d);
	d->std_fd[0] = dup(IN);
	d->std_fd[1] = dup(OUT);
	d->std_fd[2] = dup(ER);
}

#endif
