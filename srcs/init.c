#include "minishell.h"
//extern int g_code_event;

void	init_cmd(t_cmd *cmd)
{
	cmd->arg = NULL;
	cmd->path = NULL;
	cmd->str = NULL;
	cmd->ac = 0;
	cmd->here_stop = NULL;
	cmd->type = EMPTY;
	cmd->code_ret = 0;
	cmd->code_red = 0;
	cmd->redir.code_in = 0;
	cmd->redir.code_out = 0;
	cmd->env = NULL;
  	cmd->fd[0] = IN;
	cmd->fd[1] = OUT;
	cmd->fd[2] = ER;
	cmd->pipe = 0;
	cmd->fl_replace_dl = 0;
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
	using_history ();		// check this needed?
	tmp = get_env_val(d->env, LVL);
	if (tmp && ft_strlen(tmp))
		lvl = ft_atoi(tmp) + 1;
	else
		lvl = 1;
	free(tmp);
	tmp = ft_itoa(lvl);
	set_env_val(LVL, tmp, d);
	free(tmp);
//	g_code_event = 0;
	rl_catch_signals = 0;
	init_signals(d);
	d->std_fd[0] = dup(IN);
	d->std_fd[1] = dup(OUT);
	d->std_fd[2] = dup(ER);
}
