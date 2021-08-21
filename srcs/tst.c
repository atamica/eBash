#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
		while (*s++)
			i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	r;

	if (dst && src)
	{
		r = ft_strlen(src);
		if (size)
		{
			while (*src && size--)
				*dst++ = *src++;
			*dst = 0;
		}
		return (r);
	}
	return (0);
}

static size_t	kw(char const *s, char c)
{
	size_t	r;
	size_t	i;
	size_t	l;

	r = 0;
	i = 0;
	while (s[i])
	{
		l = 0;
		while (s[i] && (s[i] != c))
		{
			l++;
			i++;
		}
		if (l)
			r++;
		if (s[i])
			i++;
	}
	return (r);
}

static size_t	lw(char const *s, char c, size_t *n)
{
	size_t	i;
	size_t	l;
	char	f;

	i = 0;
	while (s[i])
	{
		l = 0;
		f = 1;
		while (s[i] && (s[i] != c))
		{
			if (f)
			{
				*n = i;
				f = 0;
			}
			l++;
			i++;
		}
		if (l)
			return (l);
		i++;
	}
	return (0);
}

static char		**mlc(char **rt, char const *s, size_t wc, char c)
{
	size_t	i;
	size_t	l;
	size_t	n;


	rt[wc] = NULL;
	i = 0;
	while (wc--)
	{
		n = 0;
		l = lw(s, c, &n);
		*(rt + i) = (char*)malloc(l * sizeof(char) + 1);
		if (*(rt + i))
		{
			s += n;
			ft_strlcpy(*(rt + i), s, l);
			s += l;
		}
		else
		{
			while (i--)
				free(*(rt + i));
			free(rt);
			return (NULL);
		}
		i++;
	}
	return (rt);
}

char			**ft_split(char const *s, char c)
{
	size_t	wc;
	char	**rt;

	if (s)
	{
		wc = kw(s, c);
		rt = (char **)malloc((wc + 1) * (sizeof(char*)));
		if (rt)
			return (mlc(rt, s, wc, c));
	}
	return (NULL);
}

int	file_x(char *path)
{
	if (access((const char*)path, X_OK))
		return (0);
	return (1);
}

int	file_exist(char *path)
{
	if (access((const char*)path, F_OK))
		return (0);
	return (1);
}

int	is_dir(char *path)
{
	int	fd;

	fd = open(path, __O_DIRECTORY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

/*
if( access( fname, F_OK ) == 0 ) {
    // file exists
} else {
    // file doesn't exist
}
// R_OK, W_OK, and X_OK		check for both read and write permission using R_OK|W_OK
// O_DIRECTORY for open
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	d;

	d = 0;
	if (s1 && s2 && n)
	{
		while ((unsigned char)*s1 && (unsigned char)*s2 && n--)
		{
			d = (unsigned char)*s1++ - (unsigned char)*s2++;
			if (d || !n)
				return (d);
		}
		return ((unsigned char)*s1 - (unsigned char)*s2);
	}
	return (d);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	l1;
	size_t	l2;

	if (s1 && s2)
	{
		l1 = ft_strlen(s1);
		l2 = ft_strlen(s2);
		r = (char*)malloc((l1 + l2 + 2) * sizeof(char));
		if (r)
		{
			ft_strlcpy(r, s1, l1);
			*(r + l1) = '/';
			ft_strlcpy(r + l1 + 1, s2, l2 + 1);
			return (r);
		}
	}
	return (NULL);
}

int main(int ac, char **av, char **env)
{
	int		i, status;
	pid_t	pid;
	char f1[] = "./includes";
	char *f2 = NULL;
	char f3[] = "/dev/tty";
	t_cmd	cmd1, cmd2;
	char	**tmp, *tmp1, *cmd0, *path, *path1, **path_f, **ptr;


	i = 0;
	cmd1=(t_cmd){"ls", "./"};
	cmd2=cmd1;

	if (ac > 1)
	{
		printf("ac=%i (%s) (%s)\n", ac, av[1], av[2]);
		if (!file_exist(av[1]))
		{
			cmd0 = NULL;
			while (*env && !cmd0)
			{
				if (!ft_strncmp(*env, "PATH=", 5))
				{
					path = *env + 5;
//					printf("%s\n", path);
					// find path+cmd
					path_f = ft_split(path, ':');
					if (path_f)
					{
						tmp = path_f;
//						printf("p::(%s)\n", *tmp);
						while (*tmp && !cmd0)
						{
							path1 = ft_strjoin(*tmp, *(av + 1));
//							printf("p_cmd::(%s) cmd=(%s)\n", path1, av[1]);
							if (file_exist(path1)) //&& file_x(path)
								cmd0 = path1;
							else
								free(path1);
							tmp++;
						}
//						printf("free\n");
						tmp = path_f;
						while (*tmp)
						{
//							printf("tmp=%p (%s)\n", *tmp, *tmp);
							tmp1 = *tmp;
							tmp++;
							free(tmp1);
						}
						free(path_f);
					}
				}
				*env++;
			}
		}
		if ((pid = fork()) < 0)
			perror("fork0");
		else if (!pid)
			exit(execve(cmd0, av + 1, env));
		pid = waitpid(pid, &status, 0);
		if (pid)
			perror("fork"); //strerror(errno)
		printf("f3:%i, f2:%i\n", file_exist(f3), file_exist(f2));
		printf("(%s %s)\n", cmd0, *(av + 2));
		free(cmd0);
		if (is_dir(f3))
			printf("(%s) is dir\n", f3);
		else
			printf("(%s) is not dir\n", f3);
	}
	return (0);
}
// gcc -o tt tmp/tst.c -I ./includes && ./tt "/bin/ls" "-la"
// void	func(char *param) __attribute__((noreturn));
// gcc -o tt tmp/tst.c -I ./includes && ./tt "ls" "-la"
