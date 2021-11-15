/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamica <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:59:26 by atamica           #+#    #+#             */
/*   Updated: 2021/11/06 12:59:37 by atamica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "get_next_line.h"
# include <signal.h>

#define FILE_PERM 0664

# define MSGE1 "\001\033[31m\002Error args!\n\001\033[0m\002"
# define MSGE2 "\001\033[31m\002Error memory!\n\001\033[0m\002"
# define MSGE3 "\001\033[31m\002Error create pipe!\n\001\033[0m\002"
# define MSGE4 "\001\033[31m\002Error open file!\n\001\033[0m\002"
# define MSGE5 "\001\033[31m\002Error create process!\n\001\033[0m\002"
# define MSGE6 "\001\033[31m\002Error in dup2!\n\001\033[0m\002"
# define MSGE7 "\001\033[31m\002Error waitpid!\n\001\033[0m\002"
# define MSGE8 "\001\033[31m\002Error in cmd!\n\001\033[0m\002"
# define MSGE9 "\001\033[31m\002Error in "
# define MSGE10 "too many arguments"
# define MSGE11 "numeric argument required"
# define MSGE12 "no such file or directory"
# define MSGE13 "syntax error near unexpected token"

# define MSG "\001\033[1;36m\002\u2328\001\033[0m\033[2C\002"
# define MSG0 ""
# define N "\n"
# define SL '/'
# define BSL '\\'
# define SQ '\''
# define DQ '"'
# define DL '$'
# define P '|'
# define T ';'
# define L '<'
# define R '>'
# define LL "<<"
# define RR ">>"

# define ERR_FATAL "error: fatal"
# define ERR_CD_BAD_ARGS "error: cd: bad arguments"
# define ERR_CD "error: cd: cannot change directory to"
# define ERR_EXE "error: cannot execute"

# define PRMT "minishell"
# define LVL "MINISHELL_LVL"

# define LINUX 1
# define OFF 0

# if OS == LINUX
#  define DIRR __O_DIRECTORY
//#  define ENV __environ
# else
#  define DIRR O_DIRECTORY
//#  define ENV environ
# endif

# ifdef PATH_MAX
#  define LEN_PATH PATH_MAX
# else
#  define LEN_PATH 4096
# endif
# define RESET "\001\033[0m\002"
# define RED "\001\033[31m\002"
# define GREEN "\001\033[32m\002"
# define YELLOW "\001\033[33m\002"
# define BLUE "\001\033[34m\002"
# define MAGENTA "\001\033[35m\002"
# define CYAN "\001\033[36m\002"

# define CTRL_C		130
# define CTRL_SL	131

int		code_event;

typedef enum e_pipe
{
	IN = STDIN_FILENO,
	OUT = STDOUT_FILENO
}	t_pipe;

typedef enum e_type
{
	EMPTY,
	BUILTINS,
	EXTERNALS,
	PIPE,
	REDIRECTIONS,
	AND,
	OR,
	OTHERS
}	t_type;

typedef enum e_redir
{
	NONE = 0,
	S_LEFT = 1,
	D_LEFT = 2,
	S_RIGHT = 4,
	D_RIGHT = 8
}	t_redir;

typedef enum e_esc_chars
{
	ESC_SQ,
	ESC_DQ,
	ESC_SL,
	ESC_SL_DQ_SQ,
	ESC_DQ_SQ,
	ESC_SL_DQ,
	ESC_SL_SQ
}	t_esc_chars;

typedef enum e_errors
{
	SUCCSESS = 0,
	ERROR = -1,
	FATAL = -2
}	t_errors;

typedef struct s_rd
{
	int		code_in;
	int		code_out;
}				t_rd;

typedef struct s_f
{
	int		pip;
	int		io;
}				t_f;

typedef struct s_fl
{
	int		fl_s_qu;
	int		fl_d_qu;
	int		fl_dol;
	int		fl_op_bkt;
	int		fl_cl_bkt;
}				t_fl;

typedef struct s_cmd
{
	char	*path;
	char	**arg;
	char	**env;
	int		fds[2];
	int		fd[2];
	t_type	type;
	t_rd	redir;
	int		code_red;
	int		pipe;
	int		code_ret;
	char	*here_stop;
	char	*str;
}				t_cmd;

typedef struct s_replace
{
	char	*src;
	char	*val;
	int		st;
	int		len;
}				t_replace;

typedef struct s_file
{
	char	*path;
	int		mode;
	int		flags;
	int		fd;
}				t_file;

typedef struct s_val
{
	int		present;
	int		position;
	char	*val;
}				t_val;

typedef struct s_stdio
{
	int		in;
	int		out;
}				t_stdio;

typedef struct s_d
{
	char	*tmp;
	char	*input;
	t_cmd	cmd;
	pid_t	cmd_pid;
	int		*pipe_fd;
	int		stat;
	int		fr;
	char	*path;
	char	*prompt;
	int		ac;
	char	**av;
	char	**env_in;
	char	**env_ex;
}				t_d;

typedef struct s_cmds
{
	t_cmd	*cmd;
	t_d		*d;
	int		cod;
	int		count;
}			t_cmds;

typedef struct s_tk
{
	int		pips;
	int		j;
	char	*end;
	char	*st;
	size_t	len;
}			t_tk;

/*
**		run.c
*/

void		cmd1(t_d *d);
void		wait_chailds(t_d *d);
int			cmd0(t_d *d);
int			run(char *str);
int			exec_cmd(t_d *d);
int			exec_cmds(t_cmds *cmds);

/*
**		parser.c
*/

int			parser(char *str, t_cmd *cmd);
int			pars(char *str, t_cmd *cmd);
void		set_flags(t_fl *fl, char c);

/*
**		utils.c
*/

char		*ft_strjoin_c(char const *s1, char const *s2, char c);
char		*ft_strjoin_m(char const *s1, char const *s2);
char		*cmdf(char *cmd);
void		dup2_check(int old_fd, int new_fd, t_d *d);
void		print_param(char **arg, char *prefix, char separator);
char		*prompt(t_d *d);

/*
**		err.c
*/

void		err_msg(char *msg, int code, t_d *d);
void		err(int code, t_d *d);
void		if_err_exit(int er, int code, t_d *d);
int			out_msg(char *msg, int code);
void		if_err_fatal(void *ptr, t_d *d);

/*
**		free.c
*/

void		free_null(void **ptr);
void		free_nu(void *ptr);
void		free2(char **ptr);
void		close_f(int fd);
void		free_d(t_d *d);
void		free_cmd(t_cmd *cmd);

/*
**		builtins/ *.c
*/

int			ft_cd(t_cmd *cmd);
int			ft_echo(t_cmd *cmd);
int			ft_pwd(void);
int			ft_env(t_d *d);
int			ft_export(t_d *d);
int			ft_exit(t_d *d);
int			ft_unset(char *name, t_d *d);

int			type_cmd(char *cmd);
int			run_builtins(t_d *d);
void		set_env_val(char *name, char *val, t_d *d);
char		*get_env_val(char **env, char *name);
int			copy_envs(t_d *d);
int			len_env_list(char **env);

/*
**		find.c
*/

char		*in_quotes(char *str, char type);
char		*replace(t_replace *r);
char		*repl_val(char *name, t_d *d);
char		*dollar(char *str, t_d *d);

/*
**		init.c
*/

void		init_cmd(t_cmd *cmd);
void		init_fl(t_fl *fl);
void		init_start(t_d *d, int ac, char **av, char **env);

/*
**		is.c
*/

int			is_builtins(char *cmd);
int			is_ext_cmd(char *cmd);
int			is_dir(char *path);
int			is_file_exist(char *path);
t_val		is_in_env_list(char **env, char *name);
// int		is_inside(char *arg);
int			is_qu(t_fl *fl);
int			is_fl(t_fl *fl);
int			is_only_digits(char *str);
int			is_in_name(char *str);

/*
**		history.c
*/

int			add_to_hist_file(const char *f_name);

/*
**		get_spec_char.c
*/

char		*ft_get_spec_char(char *str, char c, t_esc_chars escapes);
char		**ft_get_cmd_set_m(char *str, char c);
char		**ft_get_tokens(char *str);
t_errors	ft_get_redirections(char *str, t_cmd *cmd); 

/*
**		get_spec_old.c
*/

char		*ft_get_spec_ch(char *str, char c);

/*
**		redirections/herdoc.c
*/

int			err_open(int fd, t_d *d);
char		*filename(char *ptr);
int			find_redir(char *str);
//t_rd		redir(char *str, t_cmd *cmd, t_d *d);
int			get_fd(char *str, t_d *d, t_cmd *cmd);
int			rd_s_left(char *str, t_cmd *cmd, t_d *d);
int			rd_d_left(char *str, t_cmd *cmd);
int			rd_s_right(char *str, t_cmd *cmd, t_d *d);
int			rd_d_right(char *str, t_cmd *cmd, t_d *d);
int			err_open(int fd, t_d *d);

/*
**		par.c
*/

char		*replace_q(char *str, char c);
char		*replace_sq(char *str);
char  		*replace_dq(char *str, t_d *d);
//char  		*repl_dl(char *ptr, t_d *d);
char		*repl_d(char *ptr, t_d *d);
t_cmds		*pa(t_d *d);
int			pipes_count(char *str);
char		**split_cmds(t_d *d);

/*
**		srcs/signals.c
*/

void		init_signals(void);
void		recive(int signo, siginfo_t *siginfo, void *contex);
//void		recive(int signo, void *contex);
#endif
