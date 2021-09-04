#include "minishell.h"

static void	cmd1(t_d *d, char **env)
{
printf("1.path=%s ", d->cmd1.path);
print_param(d->cmd1.arg);
printf("\n");
	if (d->cmd1.path)
	{
		if (execve(d->cmd1.path, d->cmd1.arg, env) == -1)
		{
			printf("-err cmd1\n");
//			perror(MSGE8);
			strerror(errno);
			exit(errno);
		}
		exit(0);
	}
printf("err cmd1\n");
	err(8, d);
}

static void	wait_chailds(t_d *d)
{
	if (waitpid(d->cmd1_pid, &d->stat1, 0) < 0)
		err(7, d);	
	if (d->stat1)
		err_msg(MSGE8, d->stat1, d);
}

static int	cmd0(t_d *d, char **env)
{
	d->cmd1_pid = fork();
	if_err_exit(d->cmd1_pid, 5, d);
	if (d->cmd1_pid)
	{
		wait_chailds(d);
//		free_d(d);
	}	
	else
		cmd1(d, env);
	return (0);
}

int main(int ac, char **av, char **env)
{
	// init
	// tst args ?
	// input
	// parce
	// execute
	// tst status
	// free
	// exit(status)

	char	*input, path[4096];
	int		status = 1;
//	t_cmd	cmd, cmd1;
	t_d		d;

	printf("pwd=%s\n", getcwd(path, 4096)); // getting the current user's path
	while (status)
	{
		// inputing...
		input = readline("\033[36mminishell\u2328\033[0m");
		// eof
		if (!input)
		{
			status = 0;
			break;
		}
		if (input[0] == 'a')
			rl_redisplay();
		// path autocompletion when tabulation hit
		// rl_bind_key('\t', rl_complete);
		// adding the previous input into history
		add_history(input);

		/* do stuff */
		printf("start > ac=%i av=%p env=%p (%s)\n", ac, (void *)av, (void *)env, input);
		// Т. к. вызов readline() выделяет память, но не освобождает (а возвращает), то эту память нужно вернуть (освободить).
//		parser(input, &d.cmd1);
//		printf("cmd=(%s)\n", d.cmd1.path);
		printf("ret=%i\n", pars(input, &d.cmd1, __environ));
		printf("cmd=(%s) dir=%i file=%i\n", d.cmd1.path, is_dir(d.cmd1.path), file_exist(d.cmd1.path));
		cmd0(&d, env);
//		free(cmd1.path);
		free(input);
//		free(cmd.arg);
	}
	printf(MSG1);
	return (0);
}