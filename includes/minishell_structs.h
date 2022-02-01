#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef struct s_cmd
{
	char	*path;
	char	**arg;
	char	**env;
	int		ac;
	int		fd[3];
	int		std_fd[3];
	t_type	type;
	int		fl_replace;
	int		code_red;
	int		code_ret;
	char	*here_stop;
}				t_cmd;

typedef struct s_replace
{
	char	*src;
	char	*val;
	int		st;
	int		len;
}				t_replace;

typedef struct s_val
{
	int		present;
	int		position;
	char	*val;
}				t_val;

typedef struct s_d
{
	char	*tmp;
	char	*input;
	t_cmd	cmd;
	pid_t	cmd_pid;
	int		std_fd[3];
	int		*pipe_fd;
	int		stat;
	char	*path;
	char	*prompt;
	int		ac;
	char	**av;
	char	**env;
}				t_d;

typedef struct s_cmds
{
	t_cmd	*cmd;
	t_d		*d;
	int		cod;
	int		count;
	int		pipes_count;
	int		**fdp;
}			t_cmds;

typedef struct s_tk
{
	int		pips;
	int		j;
	char	*end;
	char	*st;
}			t_tk;

typedef struct s_splits
{
	int		amount;
	char	**cmds;
}				t_splits;

typedef struct s_pos
{
	char	*st;
	char	*end;
	size_t	len;
}			t_pos;

typedef struct s_fout
{
	int		fl_close;
	int		fd;
}			t_fout;
#endif
