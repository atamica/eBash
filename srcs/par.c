#include "minishell.h"

char    *replace_q(char *str, char c)
{
    char    *res;

    res = str;
    if (str)
    {
        if ((*str == c) && (str[ft_strlen(str)] == c))
        {
            res = ft_substr(str, 1, ft_strlen(str) - 2);
//          free (str);
        }
    }
    return (res);
}

char    *replace_sq(char *str)
{
    return (replace_q(str, SQ));
}

char    *replace_dq(char *str)
{
    char    *res;

    res = replace_q(str, DQ);
    
    return (res);
}

char    *repl_dl(char *ptr, t_d *d)
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
}
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