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
/* 
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
} */
/* 
char	*replace_d(t_replace *r)
{
	char	*res;
	size_t	len_src;
	size_t	len_val;

	res = NULL;
	if (r->len >= 0)
	{
		len_src = ft_strlen(r->src);
		len_val = ft_strlen(r->val);
		res = malloc(len_src - r->len + len_val + 1);
		if (res)
		{
			ft_memcpy(res, r->src, r->st);
			ft_memcpy(res + r->st, r->val, len_val);
			ft_memcpy(res + r->st + len_val, r->src + r->st + r->len, \
						len_src - r->st - r->len + 1);
		}
	}
	return (res);
} */

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

/* char	*repl_val(char *name, t_d *d)
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
			return (ft_strdup(d->av[*name - '0'])); // $0..9 = agrv[*name -'0']
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
//printf("repl_val:(%s)->(%s) len=%i\n", name, res, len);
			free(tmp);
		}			
	}
	return (res);
}
 */