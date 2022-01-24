#include "minishell.h"

/* static void	skip_sp(char *str, int *i, t_fl *fl)
{
	int	j;

	j = *i;
	while (ft_isalsp(*(str + j)) && !is_qu(fl))
		j++;
	*i = j;
} */

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

int parser0(char *str, t_cmd *cmd, t_d *d)
{
	if (str)
	{
		printf("1.(%s)\n", str);
		del_empty_sp(str);
		if (get_fd(str, d, cmd))
			return (ERROR);
		printf("2. after fd(%s)\n", str);
		// parse cmd
		del_empty_sp(str);
		cmd->arg = argc_handler(str, d, &cmd->ac);
		if (!cmd->arg)
			return (ERROR);
		// try add path
		if (is_builtins(cmd->arg[0])) // || (is_file_exist(ptr) == 1)
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

int parser(char *str, t_cmd *cmd, t_d *d)
{
	int r;
	int start;
	int i;
	char *ptr;
	t_fl fl;

	r = SUCCSESS;
	i = 0;
	init_cmd(cmd);
	init_fl(&fl);
	if (str)
	{
		del_empty_sp(str);
		// parse redir
		if_err_no_fatal(r = get_fd(str, d, cmd), 8, d);
		if (r)
			return (ERROR);
		// parse cmd
		del_empty_sp(str);
		start = i;
		while (*(str + i) && !ft_strchr(" \t;\"\'$", *(str + i)))
			i++;
		if (i == start)
			ptr = MSG0;
		else
			ptr = ft_substr(str, start, i - start);
		// try add path
		if (is_builtins(ptr)) // || (is_file_exist(ptr) == 1)
			cmd->path = ft_strdup(ptr);
		else
			cmd->path = cmdf(ptr);
		cmd->type = type_cmd(ptr);
		// printf("pars: path=%s type=%i\n", cmd->path, cmd->type);
		if (ptr && ft_strlen(ptr))
			free(ptr);
		// parse options

		// parse args
		cmd->arg = ft_split(str, ' ');
		print_param(cmd->arg, "parser:", ':');
		printf(N);
		if (cmd->path)
			r = 1;
		// parse "; | || & && >> << < >"
	}
	return (r);
}

int pars(char *str, t_cmd *cmd, t_d *d)

{
	int r;
	int start;
	int i;
	char *ptr;
	t_fl fl;

	r = 0;
	i = 0;
	init_cmd(cmd);
	init_fl(&fl);
	if (str)
	{
		// skip spases
		while (*(str + i) && ft_isalsp(*(str + i)))
			i++;
		// parse cmd
		start = i;
		while (*(str + i) && !ft_strchr(" ;\"\'$", *(str + i)))
			i++;

		ptr = ft_substr(str, start, i - start);
		// try add path
		cmd->path = cmdf(ptr);

		printf("path=%s\n", cmd->path);

		free_null((void **)&ptr);
		// cmd->arg = ft_split(str, ' ');
		while (str[i] && ft_strchr(";&|<>", str[i]))
			i++;
		ptr = ft_substr(str, start, i - start);
		cmd->arg = ft_split(ptr, ' ');
		free_null((void **)&ptr);
		/* 		if (i)
					i--; */
		if (cmd->path)
			r = 1;
		//		clear_pipes(d);
		while (str[i] && !ft_strchr(" ;&|<>", str[i]))
		{
			if (str[i] == '>')
			{
				if (str[i + 1] && str[i + 1] == '>')
				{
					d->out2redir = 1;
					i++;
				}
				else
					d->outredir = 1;
			}
			else if (str[i] == '<')
			{
				if (str[i + 1] && str[i + 1] == '<')
				{
					d->in2redir = 1;
					i++;
				}
				else
					d->inredir = 1;
			}
			else if (str[i] == '|')
			{
				if (str[i + 1] && str[i + 1] != '|')
				{
					d->double_pipe = 1;
					i++;
				}
				else
					d->pipe = 1;
			}
			else if (str[i] == '&')
			{
				if (str[i + 1] && str[i + 1] == '&')
				{
					d->double_and = 1;
					i++;
				}
			}
			i++;
		}
		str += i;
		// parse options
		// parse args
		// parse "; | || & && >> << < >"

		/*		if (i == start)
					ptr = MSG0;
				else
					ptr = ft_substr(str, start, i - start);
		//printf("pars: ptr=(%s)\n", ptr);
		// try add path
				if (is_builtins(ptr)) // || (is_file_exist(ptr) == 1)
					cmd->path = ft_strdup(ptr);
				else
					cmd->path = cmdf(ptr);
				cmd->type = type_cmd(ptr);
		//printf("pars: path=%s type=%i\n", cmd->path, cmd->type);
				free(ptr);
		// parse options

		// parse args
				cmd->arg = ft_split(str, ' ');

				if (cmd->path)
					r = 1;

		// parse "; | || & && >> << < >"
		*/
	}
	return (r);
}

void set_flags(t_fl *fl, char c)
{
	if (c == SQ && !fl->fl_d_qu)
		fl->fl_s_qu = !fl->fl_s_qu;
	if (c == DQ && !fl->fl_s_qu)
		fl->fl_s_qu = !fl->fl_s_qu;
	if (c == DL && !fl->fl_s_qu)
		fl->fl_dol = !fl->fl_dol;
}

//		******************************** parcer ********************************

int parsing_cmd(t_cmd *cmd, t_d *d)
{
	int r;
	int rd;
	t_replace what_del;

	r = SUCCSESS;
	what_del = (t_replace){.src = cmd->str, .len = 0, .st = 0, .val = MSG0};
	if (cmd->str)
	{
		del_empty_sp(cmd->str);
		// redirections
		if ((rd = find_redir(cmd->str)) > 0)
		{
			// open f's
			// char	*replace_d(t_replace *r)
			// find & cut
			r = get_fd(what_del.src, d, cmd);
		}
		if (rd < 0 || ((rd & S_LEFT) && (rd & D_LEFT)) ||
			((rd & S_RIGHT) && (rd & D_RIGHT)))
			return (ERROR);
	}
	return (r);
}
