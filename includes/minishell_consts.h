#ifndef MINISHELL_CONSTS_H
# define MINISHELL_CONSTS_H

//# define NDEBUG
//# define NDEBUG_RUN

# define FILE_PERM S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH	// 0664

# define S "\001\033"
# define E "\002"
# define MSG0 ""
# define ALL_SP " \t\v\n\f\r"
# define SP ' '
# define N "\n"
# define SL '/'
# define BSL '\\'
# define EQ '='
# define SQ '\''
# define DQ '"'
# define DL '$'
# define P '|'
# define T ';'
# define L '<'
# define R '>'
# define LL "<<"
# define RR ">>"
# define CC "^C"

# define BOLD S "[1m" E
# define DIM S "[2m" E
# define UNDERLINE S "[4m" E
# define BLINK S "[5m" E
# define INVERTED S "[7m" E
# define HIDDEN S "[8m" E

# define RESET S "[0m" E
# define BLACK S "[30m" E
# define RED S "[31m" E
# define GREEN S "[32m" E
# define YELLOW S "[33m" E
# define BLUE S "[34m" E
# define MAGENTA S "[35m" E
# define CYAN S "[36m" E
# define WHITE S "[37m" E

# define BOLD S "[1m" E
# define UNDERLINE S "[4m" E
# define INVERSED S "[7m" E

# define PRMT "minishell"
# define LVL "MINISHELL_LVL"

# define MSGE1 RED "Error args!" N RESET
# define MSGE2 RED "Error memory!" N RESET
# define MSGE3 RED "Error create pipe!" N RESET
# define MSGE4 RED "Error open file!" N RESET
# define MSGE5 RED "Error create process!" N RESET
# define MSGE6 RED "Error in dup2!" N RESET
# define MSGE7 RED "Error waitpid!" N RESET
# define MSGE8 RED "Error in cmd!" N RESET
# define MSGE9 RED "Error in "
# define MSGE10 "too many arguments"
# define MSGE11 "numeric argument required"
# define MSGE12 "no such file or directory"
# define MSGE13 "syntax error near unexpected token"
# define MSGE14 MSGE9 "signal handler" N RESET
# define MSG S "[1;36m" E "\u2328" S "[0m\033[2C" E

# define ERR_FATAL "error: fatal"
# define CD PRMT ": cd: "
# define ERR_CD_BAD_ARGS "error: cd: bad arguments"
# define ERR_CD "error: cd: cannot change directory to"
# define TOO_MANY_ARGS CD "слишком много аргументов"
# define ERR_EXE "error: cannot execute"
# define ERR_READ "error: read from STDIN"
# define REDS RED "%s" RESET
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

# define CTRL_C		130
# define CTRL_SL	131
# define CTRL_D		4

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

/* typedef enum e_esc_chars
{
	ESC_SQ,
	ESC_DQ,
	ESC_SL,
	ESC_SL_DQ_SQ,
	ESC_DQ_SQ,
	ESC_SL_DQ,
	ESC_SL_SQ
}	t_esc_chars; */

typedef enum e_errors
{
	SUCCSESS = 0,
	ERROR = -1,
	FATAL = -2
}	t_errors;

#endif