#ifndef MINISHELL_STD_LIB_H
# define MINISHELL_STD_LIB_H

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

# include <stdio.h>		// readline, printf
						// void perror(const char *s);

# if OS == LINUX		// 1
#  include <readline/readline.h>
#  include <readline/history.h>
# else					// MacOS -- ??
#  include <readline/readline.h>
#  include <readline/history.h>
# endif

# include <assert.h>

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

#endif