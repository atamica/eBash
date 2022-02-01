#include "minishell.h"

/*
**	funtion calculate args count
**	return: argc, -1 if syntax error (unpaires quotes)
*/

static int	arg_count(char *str)
{
	int		argc;
	char	flq;

	argc = 0;
	while (*str)
	{
		str = skip_spaces(str);
		if (*str == SQ || *str == DQ)
		{
			flq = *str++;
			while (*str && *str != flq)
				str++;
			if (*str++ != flq)
				return (ERROR);
			argc++;
		}
		else
		{
			argc += (*str != '\0');
			str = skip_not_spaces(str);
		}
	}
	return (argc);
}

/*
**	funtion filling args[0..ac-1] from str, split by ALL_SP
**	return: SUCCSESS (0) if succsess, else ERROR (-1): error
*/

static int	argv_fill(char *str, int ac, char **av, t_d *d)
{
	char	flq;
	char	*ptr;
	size_t	len;

	av[ac] = NULL;
	while (ac-- && *str)
	{
		str = skip_spaces(str);
		ptr = str;
		if (*str == SQ || *str == DQ)
		{
			flq = *str++;
			while (*str && *str != flq)
				str++;
			if (*str++ != flq)
				return (ERROR);
		}
		else if (*str)
			str = skip_not_spaces(str);
		len = str - ptr;
		if_err_fatal(*av++ = ft_substr(ptr, 0, len), 2, d);
	}
	if (*str)
		return (ERROR);
	return (SUCCSESS);
}

/*
**	funtion filling args[0..ac-1] from str, split by ALL_SP
**	return: char **,  if succsess, else NULL: no fatal error
**	exit if malloc return NULL 
*/

static char	**argc_handler(char *str, t_d *d, int *ac)
{
	char	**av;

	*ac = arg_count(str);
	if (*ac == ERROR)
		return (NULL);
	if_err_fatal(av = malloc(sizeof(char *) * (*ac + 1)), 2, d);
	if (argv_fill(str, *ac, av, d) == ERROR)
	{
		free2(av);
		return (NULL);
	}
	return (av);
}

int	parser(char *str, t_cmd *cmd, t_d *d)
{
	if (str)
	{
		del_empty_sp(str);
		if (get_fd(str, d, cmd))
			return (ERROR);
		del_empty_sp(str);
		cmd->arg = argc_handler(str, d, &cmd->ac);
		if (!cmd->arg)
			return (ERROR);
		if (is_builtins(cmd->arg[0]))
			cmd->path = ft_strdup(cmd->arg[0]);
		else
			cmd->path = add_path(cmd->arg[0]);
		cmd->type = type_cmd(cmd->arg[0]);
		del_quotes(cmd->arg, d->env);
	}
	return (SUCCSESS);
}
