#include "minishell.h"

static void	cmd1(t_d *d)
{
printf("1.path=%s ", d->cmd1.path);
print_param(d->cmd1.arg);
printf("\n");
	if (d->cmd1.path)
	{
		if (execve(d->cmd1.path, d->cmd1.arg, ENV) == -1)
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

static int	cmd0(t_d *d)
{
	d->cmd1_pid = fork();
	if_err_exit(d->cmd1_pid, 5, d);
	if (d->cmd1_pid)
	{
		wait_chailds(d);
//		free_d(d);
	}	
	else
		cmd1(d);
	return (0);
}

int main(void)
{
	// init
	// input
	// parce
	// execute
	// tst status
	// free
	// exit(status)

//	char	path[4096];
	int		status = 1;
	t_d		d;

//	printf("pwd=%s\n", getcwd(path, 4096)); // getting the current user's path
	while (status)
	{
		// inputing...
		d.input = readline(MSG);
		// eof
		if (!d.input)
		{
			status = 0;
			break;
		}
		/* if (d.input[0] == 'a')
			rl_redisplay(); */
		
		// path autocompletion when tabulation hit
		//rl_bind_key('\t', rl_complete);

		// adding the previous input into history
		add_history(d.input);

		/* do stuff */

		printf("ret=%i\n", pars(d.input, &d.cmd1));
		printf("cmd=(%s) dir=%i file=%i\n", d.cmd1.path, is_dir(d.cmd1.path), file_exist(d.cmd1.path));
		if (d.cmd1.path)
			cmd0(&d);

		free_d(&d);
	}
	printf(MSG1);
	rl_clear_history();
	free_d(&d);
	return (0);
}