#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>		// readline, printf
						// void perror(const char *s);

# if OS == 1			// Linux
#  include <readline/readline.h>
#  include <readline/history.h>
# else					// MacOS -- ??
#  include <readline/readline.h>
#  include <readline/history.h>
# endif

# include <unistd.h>	// int unlink(const char *pathname);
						// ssize_t read(int fd, void *buf, size_t count);
						// ssize_t write(int fd, const void *buf, size_t count);
						// int pipe(int pipefd[2]);
						// int dup(int oldfd);
						// int dup2(int oldfd, int newfd);
						// int execve(const char *pathname, char *const argv[], 
						// 			char *const envp[]);
						// pid_t fork(void);
						// int close(int fd);
						// char *getcwd(char *buf, size_t size);
						// int chdir(const char *path);
						// int isatty(int fd);
						// char *ttyname(int fd);
						// int ttyslot(void);

# include <signal.h>	// typedef void (*sighandler_t)(int);
						// sighandler_t signal(int signum, 
						// 		sighandler_t handler);
						// int kill(pid_t pid, int sig);

# include <sys/types.h>	// int open(const char *pathname, 
# include <sys/stat.h>	// 		int flags, mode_t mode);
# include <fcntl.h>		// int stat(const char *pathname, 
						// 		struct stat *statbuf);
						// int fstat(int fd, struct stat *statbuf);
						// int lstat(const char *pathname, 
						// 		struct stat *statbuf);

# include <dirent.h>	// DIR *opendir(const char *name);
						// struct dirent *readdir(DIR *dirp);
// struct dirent {
// 	ino_t          d_ino;       /* Inode number */
// 	off_t          d_off;       /* Not an offset; see below */
// 	unsigned short d_reclen;    /* Length of this record */
// 	unsigned char  d_type;      /* Type of file; */
// 	char           d_name[256]; /* Null-terminated filename */
// };
						// int closedir(DIR *dirp);


# include <curses.h>	// int tputs(const char *str, int affcnt, 
						// 		int (*putc)(int));
# include <sys/ioctl.h>	// int ioctl(int fd, unsigned long request, ...);

# include <termios.h>	// int tcgetattr(int fd, struct termios *termios_p);
						// int tcsetattr(int fd, int optional_actions, 
						// 		const struct termios *termios_p);
# include <term.h>		// int tgetent(char *bp, const char *name);
						// int tgetflag(char id[2]);
						// int tgetnum(char id[2]);
						// char *tgetstr(char id[2], char **area);
						// char *tgoto(char *cap, int col, int row);
						// cc [ flag... ] file... -I /usr/xpg4/include -L
						// /usr/xpg4/lib -R  /usr/xpg4/lib 
						// -lcurses  [ library... ]
						// 
						// c89 [ flag... ] file... -lcurses [ library... ]

# include <stdlib.h>	// malloc, free, exit
						// char *getenv(const char *name);

# include <errno.h>		// errno

# include <string.h>	// char *strerror(int errnum);

# include <sys/wait.h>	// pid_t wait(int *wstatus);
						// pid_t waitpid(pid_t pid, int *wstatus, int options);

# include "libft.h"

# define MSGE1 "\033[31mError args!\n\033[0m"
# define MSGE2 "\033[31mError memory!\n\033[0m"
# define MSGE3 "\033[31mError create pipe!\n\033[0m"
# define MSGE4 "\033[31mError open file!\n\033[0m"
# define MSGE5 "\033[31mError create process!\n\033[0m"
# define MSGE6 "\033[31mError in dup2!\n\033[0m"
# define MSGE7 "\033[31mError waitpid!\n\033[0m"
# define MSGE8 "\033[31mError in cmd!\n\033[0m"
# define MSGE9 "\033[31mError in "

# define MSG "\033[36mminishell\u2328\033[0m"
# define MSG1 "\n"

# define LINUX 1

# if OS != LINUX
#  define DIRR O_DIRECTORY
#  define ENV environ
# else
#  define DIRR __O_DIRECTORY
#  define ENV __environ
# endif

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
extern char ** environ;

typedef enum e_pipe {IN, OUT}	t_pipe;

typedef struct s_cmd
{
	char	*path;
	char	**arg;
}				t_cmd;

typedef struct s_file
{
	char	*path;
	int		mode;
	int		flags;
	int		fd;
}				t_file;

typedef struct s_stdio
{
	int		in;
	int		out;
}				t_stdio;

typedef struct s_d
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	t_file	file1;
	t_file	file2;
	int		*pipe_fd;
	pid_t	cmd1_pid;
	pid_t	cmd2_pid;
	int		stat1;
	int		stat2;
	int		fr;
	char	*input;
}				t_d;

/*
**		parser.c
*/

void	parser(char *input, t_cmd *cmd);
int		pars(char *str, t_cmd *cmd);

/*
**		utils.c
*/

int		is_dir(char *path);
int		file_exist(char *path);
char	*ft_strjoin_m(char const *s1, char const *s2);
// void	free_mem(char **ptr);
char	*cmdf(char *cmd);
void	dup2_check(int old_fd, int new_fd, t_d *d);
void	print_param(char **arg);

/*
**		err.c
*/

void	err_msg(char *msg, int code, t_d *d);
void	err(int code, t_d *d);
void	if_err_exit(int er, int code, t_d *d);
int		out_msg(char *msg, int code);

/*
**		free.c
*/

void	free_null(void **ptr);
void	free_nu(void *ptr);
void	free2(char **ptr);
void	close_f(int fd);
void	free_d(t_d *d);

/*
**		free.c
*/

int		cd(t_cmd *cmd);
int		check_builtins(char *cmd);

#endif
