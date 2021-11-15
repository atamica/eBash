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
	pos = ft_strchr(ptr, DL);
	while (pos && is_in_name(pos + 1))
	{
		r = (t_replace){.st = pos - res, .len = 2};
		while (pos[r.len] && is_in_name(pos + r.len))
			r.len++;
		name = ft_substr(res + r.st, 1, r.len - 1);
		r = (t_replace){.src = res, r.val = get_env_val(d->env_in, name)};
		tmp = replace(&r);
		if (res != ptr)
			free (res);
		res = tmp;
		free (name);
		pos = ft_strchr(res + ft_strlen(r.val) - r.len, DL);
		free (r.val);
	}
	return (res);
}

/* t_cmd	*pars_cmd(char **tokens, int i, )
{

} */

t_cmds	*pa(t_d *d)
{
	t_cmds	*cm;
	int		i;
	char	**tmp;

	i = 0;
	cm = malloc(sizeof(t_cmds));
	if_err_fatal(cm, d);
	*cm = (t_cmds){.d = d, .cod = 0, .count = 0, .cmd = NULL};
	tmp = split_cmds(d);
/* printf("pa: (%s)\n", *tmp);
print_param(tmp, "pa:", ' ');
printf(N); */
	if (!tmp)						// err or do nothing
		return (cm);
	while (tmp[i])
		i++;						// i = count of tokens
	cm->count = i;
	cm->cmd = malloc(sizeof(t_cmd) * (i + 1));
	if_err_fatal(cm->cmd, d);
	i = -1;
	while (tmp[++i])
	{
		cm->cmd[i].str = repl_d(tmp[i], d);
printf("pa:(%s) -> {%s}\n", tmp[i], cm->cmd[i].str);
//		cm->cmd[i] = pars_cmd();
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
		ptr = ft_get_spec_ch(str, P);
		while (ptr)
		{
			ptr = ft_get_spec_ch(ptr + 1, P);
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
	if (t.st)
	{
		if_err_fatal(res = malloc(sizeof(char *) * (t.pips + 1)), d);
		if (t.pips)
		{
			t.len = ft_get_spec_ch(t.st, P) - t.st;
			while (t.j < t.pips)
			{
				res[t.j++] = ft_substr(t.st, 0, t.len);
				t.st += t.len + 1;
				t.end = ft_get_spec_ch(t.st, P);
				if (t.end)
					t.len = t.end - t.st;
			}
		}
		res[t.j++] = ft_substr(t.st, 0, ft_strlen(t.st));
	}
	res[t.j] = NULL;
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
            tmp = get_env_val(d->env_in, name);
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
			r.val = get_env_val(d->env_in, name);
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