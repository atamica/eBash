#include "minishell.h"

/*
**	funtion calculate args count
**	return: argc, -1 if syntax error (unpaires quotes)
*/

static int arg_count(char *str)
{
	int argc;
	char flq;

	argc = 0;
	while (*str)
	{
		str = skip_spa(str);
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
			while (*str && !ft_strchr(ALL_SP, *str))
				str++;
		}
	}
	return (argc);
}

static int argv_fill(char *str, int ac, char **av, t_d *d)
{
	int i;
	char flq;
	char *ptr;
	size_t len;

	i = 0;
	av[ac] = NULL;
	while (i < ac && *str)
	{
		str = skip_spa(str);
		if (*str == SQ || *str == DQ)
		{
			ptr = str;
			flq = *str++;
			while (*str && *str != flq)
				str++;
			if (*str++ != flq)
				return (ERROR);
			len = str - ptr;
			if_err_fatal(av[i] = ft_substr(ptr, 0, len), 2, d);
			i++;
		}
		else if (*str)
		{
			ptr = str;
			while (*str && !ft_strchr(ALL_SP, *str))
				str++;
			len = str - ptr;
			if_err_fatal(av[i] = ft_substr(ptr, 0, len), 2, d);
			i++;
		}
	}
	if (*str)
		return (ERROR);
	return (SUCCSESS);
}

static char **argc_handler(char *str, t_d *d, int *ac)
{
	char **av;

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

int parser(char *str, t_cmd *cmd, t_d *d)
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
			cmd->path = cmdf(cmd->arg[0]);
		cmd->type = type_cmd(cmd->arg[0]);
#ifdef NDEBUG
		printf("pars: path=%s type=%i\n", cmd->path, cmd->type);
#endif
		del_quotes(cmd->arg, d);
#ifdef NDEBUG
		print_param(cmd->arg, "parser:", ':');
		printf(N);
#endif
	}
	return (SUCCSESS);
}
