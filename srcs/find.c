#include "minishell.h"

/* static is_pair_quotes(char *str, char type)
{
	int count;

	count = 0;
	if (str && type)
		while (*str)
			if (*str++ == type)
				count++;
	return (!(count % 2));
} */

char	*in_quotes(char *str, char type)
{
	char	*res;
	int		st;
	int		end;

	res = NULL;
	if (ft_strchr(str, type))
		st = ft_strchr(str, type) - str + 1;
	else
		st = -1;
	if (str && (st > -1) && *(str + st + 1))
		end = ft_strchr(str + st + 1, type) - str;
	else
		end = -1;
	if ((st > -1) && (end > -1))
		res = ft_substr(str, st, end - st);
	return (res);
}

char	*replace_d(t_replace *r)
{
	char	*res;
	size_t	len0;
	size_t	len1;

	res = NULL;
	if (r->len > -1)
	{
		len0 = ft_strlen(r->src);
		len1 = ft_strlen(r->val);
		res = malloc(len0 - r->len + len1 + 1);
		if (res)
		{
			ft_memcpy(res, r->src, r->st);
			ft_memcpy(res + r->st, r->val, len1);
			ft_memcpy(res + r->st + len1, r->src + r->st + r->len + 1, \
						len0 - r->st - r->len);
		}
	}
	return (res);
}

/* char	*dollar(char *str, t_d *d)
{
	char		*res;
	char		*tmp;
	t_replace	r;

	res = NULL;
	if (str)
	{
		tmp = ft_strchr(str, '$');
		if (tmp)
		{
			r.src = str;
			r.st = tmp - str + 1;
			tmp++;
			if (ft_isdigit(*tmp))
			{
				if (d->av[*tmp - '0'])
					return (ft_strdup(d->av[*tmp - '0']));		// $0..$9
				else
					return (ft_strdup(MSG0));
			}
			if (*tmp == '#')
				return (ft_itoa(d->ac));
			if (ft_isalpha(*tmp))
			{
				while (*tmp && (ft_isalnum(*tmp) || (*tmp == '_')))
					tmp++;
				r.len = tmp - str - r.st;
				tmp = ft_substr(str, r.st, r.len);
				r.val = getenv(tmp);
				free(tmp);
				r.len++;
				r.st--;
				res = replace_d(&r);
			}
		}
	}
	return (res);
} */


/*
**	return, value $[NAME]
*/

char	*repl_val(char *name, t_d *d)
{
	int		len;
	char	*res;
	char	*tmp;

	res = NULL;
	if (name)
	{
		if (!*name)
			return ("$");
		if (*name == '$')
			return (ft_itoa(getpid()));	// getpid ?
		if (ft_isdigit(*name))
			return (ft_strdup(d->av[*name - '0']));	// $0..9 = agrv[*name -'0']
		if (*name == '#')
			return (ft_itoa(d->ac));		// $#, agrvc
		if (*name == '_')
			return (getenv("_"));	// $_ = prev cmd, take from history
		if (ft_isalpha(*name))
		{						// $[NAME]
			len = 0;
			while (*name && (ft_isalnum(*name) || (*name == '_')))
				len++;
			tmp = ft_substr(name, 0, len);
			res = getenv(tmp);
printf("repl_val:(%s)->(%s) len=%i\n", name, res, len);
			free(tmp);
		}			
	}
	return (res);
}

/* int	find_dol(char *str, t_replace *r)
{
	int		res;
	char	*tmp;

	res = 0;
	tmp = ft_strchr(str, '$');
	if (tmp)
	{
		r->st = tmp - str;
		r->len = 0;
		res = 1;
	}
	else
		*r = (t_replace){.len = -1, .src = NULL, .st = 0, .val = NULL};
	return (res);
} */
/* 
char	*repl_var(char *str)
{
	int		st;
	int		len;
	char	*res;
	char	*tmp;
	int		fl_quo1;
	int		fl_quo2;
	t_replace	r;

	res = MSG0;
	if (str)
	{
		// if !'
		tmp = ft_strchr(str, '$');
		
		if (tmp)
		{
			st = tmp - str + 1;
			tmp++;
			if ((*tmp == '0') || (*tmp == '_'))
				return (PRMT); 		// $0, $_ = bash
			if (ft_isdigit(*tmp))
				return (MSG0);		// $1..$9
			if (ft_isalpha(*tmp))
			{						// $USER, ect
				while (*tmp && (ft_isalnum(*tmp) || (*tmp == '_')))
					tmp++;
				len = tmp - str - st;
				tmp = ft_substr(str, st, len);
printf("dol:(%s) st=%i, len=%i\n", tmp, st, len);
				res = getenv(tmp);
				free(tmp);
				return (res);
			}			
		}
	}
	return (res);
} */

/* int	args_count(char *str)
{
	int		st;
	int		end;
	int		res;
	t_fl	fl;
	char	*tmp;

	res = 0;
	init_fl(&fl);
	tmp = str;
	while (*tmp && ft_isalsp(*tmp))	// skip whitespaces
		tmp++;
	if (!*tmp)						// empty line
		return(res);
	st = tmp - str;
	while (*tmp && !ft_strchr(" ;", *tmp))	// find end of CMD
		tmp++;
	res++;
	if (!*tmp)						// 1 arg = CMD
		return(res);
	end = tmp - str;
	while (*tmp && ft_isalsp(*tmp))	// skip whitespaces
		tmp++;


	return (res);
} */