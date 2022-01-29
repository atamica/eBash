#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef enum e_pipe
{
	IN = STDIN_FILENO,
	OUT = STDOUT_FILENO,
	ER = STDERR_FILENO
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

/*
**	|.bit.|4|3|2|1|0|
**	-----------------
**		  |0|0|0|0|0| = 0 (NONE)
**		  |0|0|0|0|1| = 1 (S_LEFT)
**		  |0|0|0|1|0| = 2 (D_LEFT)
**		  |0|0|1|0|0| = 4 (S_RIGHT)
**		  |0|1|0|0|0| = 8 (D_RIGHT)
**	if ((rd & 3) || (rd & 12)) then syntax error
**	else	Ok
*/

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

typedef struct s_bin_str
{
	size_t		len;
	char const	*string;
}				t_bin_str;

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

typedef struct s_io
{
	int		in;
	int		out;
	int		err;
}				t_io;

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
	int		ac;
	int		fd[3];
	int		std_fd[3];
	t_type	type;
	t_rd	redir;
	int		fl_replace_dl;
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
	int		std_fd[3];
	int		*pipe_fd;
	int		stat;
	int		fr;
/* 	int		pipe;
	int		inredir;
	int		outredir;
	int		in2redir;
	int		out2redir;
	int		double_pipe;
	int		double_and; */
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

typedef struct s_a
{
	char	*tmp;
	char	*input;
	t_cmds	*cmds;
	int		*pipe_fd;
	int		stat;
	int		fr;
	char	*prompt;
	int		ac;
	char	**av;
	char	**env;
	char	**env_ex;
}				t_a;

typedef struct s_splits
{
	int		amount;
	char	**cmds;
}				t_splits;

typedef struct s_exe
{
	int		code;
	char	*path;
	char	**args;
	char	**env;
	int		fd[2];
	int		fdp[2];
}				t_exe;

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
