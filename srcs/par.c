#include "minishell.h"

char	*replace_q(char *str, char c)
{
	char	*res;

	res = str;
	if (str)
	{
		if ((*str == c) && (str[ft_strlen(str) - 1] == c))
		{
			res = ft_substr(str, 1, ft_strlen(str) - 2);
			free (str);
		}
	}
	return (res);
}

char	*replace_sq(char *str)
{
	return (replace_q(str, SQ));
}

char	*replace_dq(char *str, t_d *d)
{
	return (replace_q(repl_dlr(str, d), DQ));
}

void	del_quotes(char **arg, t_d *d)
{
#ifdef NDEBUG	
	char **st = arg;

	print_param(arg, "del_q_before", '\n');
	printf("\n--------\n");
#endif
	while (*arg)
	{
		del_empty_sp(*arg);
		if (**arg == SQ)
			*arg = replace_sq(*arg);
		else if (**arg == DQ)
			*arg = replace_dq(*arg, d);
		else
			*arg = repl_dlr(*arg, d);
		arg++;
	}
#ifdef NDEBUG
	print_param(st, "del_q_after", '\n');
	printf(N);
#endif
}

char	*repl_dlr(char *ptr, t_d *d)
{
	t_replace	r;
	char		*res;
	char		*pos;
	char		*tmp;
	char		*name;

	pos = get_pos_char(ptr, DL);
	res = ptr;
	while (pos)
	{
		r = (t_replace){.src = res, .val = NULL, .st = pos - res, .len = 0};
		while (is_in_name(pos + r.len + 1))
			r.len++;
		if (r.len)
		{
			name = ft_substr(res + r.st, 1, r.len++);
			r.val = get_env_val(d->env, name);
			free (name);
			tmp = replace_d(&r);
 			if (res != ptr)
				free (res);
			res = tmp;
			r.st += ft_strlen(r.val) - r.len - 1;
			free (r.val);
		}
		else
			r.st++;
		pos = get_pos_char(res + r.st, DL);
	}
	return (res);
}

char	*skip_sps(char *ptr)
{
	if (ptr)
	{
		while (*ptr && ft_isalsp(*ptr))
			ptr++;
	}
	return (ptr);
}

t_cmds	*pa2(t_d *d)
{
	t_cmds		*cm;
	int			i;
	t_splits	*tmp;

	if_err_fatal(cm = malloc(sizeof(t_cmds)), 2, d);
	*cm = (t_cmds){.d = d, .cod = 0, .count = 0, .cmd = NULL};
	tmp = split_cmds2(d);
	if (*tmp->cmds)
	{
		cm->count = tmp->amount;
		cm->pipes_count = cm->count - 1;
		if (cm->pipes_count > 0)
		{
			if_err_fatal(cm->fdp = malloc(sizeof(int*) * (cm->pipes_count)), \
																		2, d);
			i = -1;
			while (++i < cm->pipes_count)
				if_err_fatal(cm->fdp[i] = malloc(sizeof(int) * 2), 2, d);
		}
		if_err_fatal(cm->cmd = malloc(sizeof(t_cmd) * (cm->count + 1)), 2, d);
		i = -1;
		while (tmp->cmds[++i])
		{
			init_cmd(cm->cmd + i);
			cm->cmd[i].str = tmp->cmds[i];
			cm->cod = parser(cm->cmd[i].str, cm->cmd + i, d);
			cm->cmd[i].env = d->env;
		}
		cm->cmd[i].type = EMPTY;
		free2(tmp->cmds);
		free(tmp);
	}
	return (cm);
}

int	pipes_count(char *str)
{
	int		l;
	char	*ptr;

	l = 0;
	if (str && *str)
	{
		ptr = get_pos_char(str, P);
		while (ptr++)
		{
			ptr = get_pos_char(ptr, P);
			l++;
		}
	}
	return (l);
}

/*
**	split by '|'
**	need add also split by other: ';', "&&" "||"
*/

t_splits	*split_cmds2(t_d *d)
{
	t_tk		t;
	t_splits	*res;

	if_err_fatal(res = malloc(sizeof(t_splits)), 2, d);
	t = (t_tk){.j = 0, .pips = pipes_count(d->input), .st = d->input};
	res->amount = 0;
	if (t.st)
	{
		res->amount = t.pips + 1;
		if_err_fatal(res->cmds = malloc(sizeof(char *) * (t.pips + 2)), 2, d);
		while (t.pips--)
		{
			t.end = get_pos_char(t.st, P);
			res->cmds[t.j++] = ft_substr(t.st, 0, t.end - t.st);
			t.st = t.end + 1;
		}
		res->cmds[t.j++] = ft_substr(t.st, 0, ft_strlen(t.st));
	}
	res->cmds[t.j] = NULL;
	return (res);
}
