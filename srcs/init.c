#include "minishell.h"
//extern int code_event;

static void	init_cmd0(t_cmd *cmd)
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

void	init_cmd(t_cmd *cmd)
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
//	char	*promt;
//	char	p[LEN_PATH];


# if OS == LINUX
	rl_clear_history();
# endif
	init_cmd0(&d->cmd);
	d->ac = ac;
	d->av = av;
	d->env_ex = env;
	d->tmp = ft_strdup(MSGE5);
	free(d->tmp);
	copy_envs(d);
	using_history ();
	tmp = getenv(LVL);
	if (ft_strlen(tmp))
	{
		lvl = ft_atoi(tmp) + 1;
		free(tmp);
	}
	else
		lvl = 1;
	tmp = ft_itoa(lvl);
	set_env_val(LVL, tmp, d);
	free(tmp);
	code_event = 0;
	init_signals();
//	set_env_val("SHELL", "minishell", d);
//	printf("pwd=%s\n", getcwd(path, LEN_PATH)); // getting the current user's path
}
