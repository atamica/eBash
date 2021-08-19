#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>	// int access(const char *pathname, int mode);
						// int unlink(const char *pathname);
						// ssize_t read(int fd, void *buf, size_t count);
						// ssize_t write(int fd, const void *buf, size_t count);
						// int pipe(int pipefd[2]);
						// int pipe2(int pipefd[2], int flags);
						// int dup(int oldfd);
						// int dup2(int oldfd, int newfd);
						// int execve(const char *pathname, char *const argv[], char *const envp[]);
						// pid_t fork(void);
						// 

# include <sys/types.h>	// int open(const char *pathname, int flags, mode_t mode);
# include <sys/stat.h>	// -/-
# include <fcntl.h>		// -/-

# include <stdlib.h>	// malloc, free, exit

# include <stdio.h>		// void perror(const char *s);
# include <errno.h>		// ?

# include <string.h>	// char *strerror(int errnum);

# include <sys/wait.h>	// pid_t wait(int *wstatus);
						// pid_t waitpid(pid_t pid, int *wstatus, int options);

# define MSGE1 "\033[31mError args!\n\033[0m"
# define MSGE2 "\033[31mError memory!\n\033[0m"
# define MSGE3 "\033[31mError create process!\n\033[0m"


# define MSG1 "\n"

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"

typedef struct	s_cmd
{
	char	*cmd;
	char	*path;

}				t_cmd;

/*
**		split.c
*/

char	**ft_split(char const *s, char c);

/*
**		utils.c
*/

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_m(char const *s1, char const *s2);

/*
**		utils1.c
*/

int		file_x(char *path);
int		file_exist(char *path);
int		is_dir(char *path);

/*
**		utils2.c
*/

char	*cmdf(char *cmd, char **env);

/*
**		check.c
*/

int		check_arg(int ac, char **av, char **env);

/*
**		err.c
*/

void	err_msg(char *msg, int code);

#endif
