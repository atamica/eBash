#include "minishell.h"

char	*replace_q(char *str, char c)
{
	char	*res;

	res = str;
	if (str)
	{
		if ((*str == c) && (str[ft_strlen(str)] == c))
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
	char	*res;

	str = replace_q(str, DQ);
	res = repl_d(str, d);
	free (str);
	return (res);
}

char	*repl_d(char *ptr, t_d *d)
{
	t_replace	r;
	char		*res;
	char		*pos;
	char		*tmp;
	char		*name;

	res = ptr;
	pos = get_pos_char(res, DL);
	while (pos)
	{
		r = (t_replace){.st = pos - res, .len = 0};
		while (is_in_name(pos + r.len))
			r.len++;
		if (r.len)
		{
			name = ft_substr(res + r.st, 1, r.len);
			r.src = res;
			r.val = get_env_val(d->env, name);
			tmp = replace(&r);
			free (res);
			res = tmp;
			free (name);
		}
		pos = get_pos_char(res + r.st, DL);
		free (r.val);
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

t_cmd	*pars_cmd(t_cmd *cmd, t_d *d)
{
	char	*st;

	init_cmd0(cmd);
	st = skip_sps(cmd->str);
	if (st && *st)
	{
		// CMD is not EMPTY
		// pars CMD
printf("pars_cmd: (%s)\n", d->input);
	}
	return (cmd);
}

/* while (*st && ft_isalsp(st))
			st++;
		if (!(*st))
		{
			if (cmd[i + 1].str)
				cmd->pipe = 1;
			return ;	//		empty cmd
		}
			
		if (*st == L || *st == R) */

t_cmds	*pa(t_d *d)
{
	t_cmds	*cm;
	int		i;
	char	**tmp;

	i = 0;
	if_err_fatal(cm = malloc(sizeof(t_cmds)), 2, d);
	*cm = (t_cmds){.d = d, .cod = 0, .count = 0, .cmd = NULL};
	tmp = split_cmds(d);
//print_param(tmp, "pa:", ' ');
//printf(N);
	if (tmp)						// err or do nothing
	{
		while (tmp[i])
			i++;						// i = count of tokens
		cm->count = i;
		if_err_fatal(cm->cmd = malloc(sizeof(t_cmd) * (i + 1)), 2, d);
		i = -1;
		while (tmp[++i])
		{
			cm->cmd[i].str = repl_d(tmp[i], d);
			parser(cm->cmd[i].str, cm->cmd + i);
			
printf("_pa:(%s) -> {%s}\n", tmp[i], cm->cmd[i].str);
//		cm->cmd[i] = pars_cmd();
		}
		cm->cmd[i].type = EMPTY;
		free2(tmp);
	}
	return (cm);
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
		if_err_fatal(cm->cmd = malloc(sizeof(t_cmd) * (cm->count + 1)), 2, d);
		i = -1;
		while (tmp->cmds[++i])
		{
			init_cmd0(cm->cmd + i);
//			del_empty_sp(tmp->cmds[i]);
			cm->cmd[i].str = repl_d(tmp->cmds[i], d);
			parser(cm->cmd[i].str, cm->cmd + i);
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

char	**split_cmds(t_d *d)
{
	t_tk	t;
	char	**res;

	res = NULL;
	t = (t_tk){.j = 0, .pips = pipes_count(d->input), .st = d->input};
	if (t.st && *t.st)
	{
		if_err_fatal(res = malloc(sizeof(char *) * (t.pips + 2)), 2, d);
		while (t.pips--)
		{
			t.end = get_pos_char(t.st, P);
			res[t.j++] = ft_substr(t.st, 0, t.end - t.st);
			t.st = t.end + 1;
		}
		res[t.j++] = ft_substr(t.st, 0, ft_strlen(t.st));
	}
	res[t.j] = NULL;
	return (res);
}

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

/* int fill_cmd(t_cmd *cmd, t_d *d, t_cmds *cmds, char **tok)
{
    int rd_count;

    rd_count = 0;
    while (*tok)
    {
        if (**tok == L || **tok == R)   // rd begin
        {

        }

        tok++;
    }
    return (SUCCSESS);
} */

/* 
char	*repl_dl(char *ptr, t_d *d)
{
    t_replace   r;
    char        *res;
    char        *pos;
    char        *tmp;
    char        *name;
    int         offs;
    int         len;
    int         dg;
    int         l;
    char        c;

    len = ft_strlen(ptr);
    pos = ft_strchr(ptr, DL);
    offs = pos - ptr;
printf("repl: len(%i) of(%i)\n", len, offs);  
    res = ptr;
    while (pos && (offs < len))
    {
        if (*(pos + 1) == '#')
        {
            tmp = ft_itoa(d->ac);
            r = (t_replace){.src = res, .val = tmp, .st = offs, .len = 2};
            res = replace(&r);
            free(tmp);
        }
        else if (ft_isdigit(*(pos + 1)))
        {
            dg = *(pos + 1) - '0';
            if (d->ac >= dg)
                tmp = d->av[dg];
            else
                tmp = MSG0;
            r = (t_replace){.src = res, .val = tmp, .st = offs, .len = 2};
            res = replace(&r);
        } 
        else if (ft_isalnum(*(pos + 1)) || (*(pos + 1) == '_'))
        {
            l = 0;
            while (*(pos + 1 + l) && (ft_isalnum(*(pos + 1 + l)) || (*(pos + 1 + l) == '_')))
                l++;
            name = ft_substr(pos, 1, l);
printf("repl: name(%s)\n", name);           
            tmp = get_env_val(d->env, name);
printf("repl: val(%s)\n", tmp);
printf("repl:- len(%i) of(%i)\n", len, offs); 
            r = (t_replace){.src = res, .val = tmp, .st = offs, .len = l + 1};
            free (tmp);
            tmp = res;
            res = replace(&r);
printf("repl: ---(%s)\n", res);  
            free (tmp);
            free (name);
        }
printf("repl: +(%s)\n", res);
        tmp = ft_strchr(ptr + offs, DL);
        if (tmp)
            offs = tmp - ptr;
        else
            break ;
        len = ft_strlen(res);
printf("repl:++ len(%i) of(%i)\n", len, offs);
        if (offs < len)
            pos = ft_strchr(res + offs, DL);
        else
            pos = NULL;
        c = getchar();
		if (c)
			c = 0;
    }
    return (res);
} */
/* 
int fill_cmd(t_cmd *cmd, t_d *d, t_cmds *cmds, char **tok)
{
    int rd_count;

    rd_count = 0;
    while (*tok)
    {
        if (**tok == L || **tok == R)   // rd begin
        {

        }

        tok++;
    }
    return (SUCCSESS);
} */

/* char	*repl_d(char *ptr, t_d *d)
{
	t_replace   r;
    char        *res;
    char        *pos;
    char        *tmp;
    char        *name;
    int         offs;
	int			i = 0;

	pos = ft_strchr(ptr, DL);
	if (!pos)
		return (ptr);
	res = ptr;
	offs = pos - res;
	while (*pos)
	{
		if (is_in_name(pos + 1))
		{
			i++;
			r.st = pos++ - res;
			r.len = 2;
			while (*pos && is_in_name(pos))
			{
				r.len++;
				pos++;
			}
			r.src = res;
			name = ft_substr(res + r.st, 1, r.len - 1);
			r.val = get_env_val(d->env, name);
			tmp = replace(&r);
			free (res);
			res = tmp;
			free (tmp);
			free (name);
			pos = res + offs - r.len + ft_strlen(r.val);
			free (r.val);
		}
		pos++;
	}
printf("$:res:%i(%s)\n", i, res);
	return (res);
} */
