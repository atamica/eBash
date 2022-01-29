#include "minishell.h"



//#define EOWNERDEAD		130
//#define ENOTRECOVERABLE	131

/* void	next(int signo)
{
	if (signo)
		signo = 0;
}

void	error_msg(void)
{
	write(1, "Not good arguments, must be 2 args\n", 36);
}

void	check_args(int argc, char *argv, int *pid)
{
	if (argc != 3)
	{
		error_msg();
		exit(0);
	}
	*pid = ft_atoi(argv);
	if (*pid <= 0 )
	{
		write(1, "Wrong pid!\n", 11);
		exit(0);
	}
}

void	init_signals(void)
{
	signal(SIGUSR1, next);
	signal(SIGUSR2, next);
} */

/* void	check_print(unsigned char *counter, unsigned char *out_char)
{
	if (*counter == 0)
	{
		write(1, out_char, 1);
		*out_char = 0;
		*counter = 64;
	}
} */

void	recive(int signo, siginfo_t *siginfo, void *contex)
//void	recive(int signo, void *contex)
{
	//static int				old_pid;
	//static unsigned char	out_char;
	//static unsigned char	counter;
//	int						pid_in;
	//int n;
	//char buf[3];

	(void)contex;
	(void)siginfo;
//	pid_in = siginfo->si_pid;
/* 	if (!pid_in)
		pid_in = old_pid;
	old_pid = pid_in;
	if (!counter)
		counter = 128;
	if (signo || contex)
	{
	} */
	if (signo == SIGINT)
	{	
		
		//printf("CTRL+C pressed\n");
		//g_code_event = CTRL_C;
		//ft_putchar_fd('\b', 1);
		ft_putendl_fd(CC, ER);	// OUT ?
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		//exit(EOWNERDEAD);
	}
	else if (signo == SIGQUIT)
	{
		//printf("CTRL+\\ pressed\n");
		//g_code_event = CTRL_SL;
		//if (read(1, buf, 1) != 1)
		//exit(ENOTRECOVERABLE);
		
	}
/* 	wait(&n);
	if (n == 2 || n == 3)
	{
		if (signo == SIGINT)
			ft_putchar_fd('\r', 1);
		if (signo == SIGQUIT)
			ft_putendl_fd("Quit: 3", 1);
	} */
	//check_print(&counter, &out_char);
	//usleep(100);
	//kill(pid_in, SIGUSR1);

}

void	init_signals(void)
{
	sigset_t			set;
	struct sigaction	act_kill;
	struct sigaction	act_quit;
//	struct sigaction	act_eof;

	sigfillset(&set);
	ft_memset(&act_kill, 0, sizeof(act_kill));
	act_kill.sa_handler = (void *)recive;
//	act_kill.sa_flags = SA_SIGINFO;
	act_kill.sa_mask = set;
	sigaction(SIGINT, &act_kill, NULL);
	ft_memset(&act_quit, 0, sizeof(act_quit));
	act_quit.sa_sigaction = recive;
	act_quit.sa_flags = SA_SIGINFO;
	act_quit.sa_mask = set;
	sigaction(SIGQUIT, &act_quit, NULL);
/* 	ft_memset(&act_eof, 0, sizeof(act_eof));
	act_eof.sa_sigaction = recive;
	act_eof.sa_flags = SA_SIGINFO;
	act_eof.sa_mask = set;
	sigaction(SIGUSR1, &act_eof, NULL); */
}
