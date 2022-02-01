#include "minishell.h"

/*
**	delite char c from begin and end of str
*/

void	del_quo(char *str, char c)
{
	size_t	len;

	if (str)
	{
		len = ft_strlen(str);
		if ((len > 1) && (*str == c) && (str[len - 1] == c))
		{
			ft_memmove(str, str + 1, len - 2);
			str[len - 2] = '\0';
		}
	}
}

char	*replace_sq(char *str)
{
	del_quo(str, SQ);
	return (str);
}

char	*replace_dq(char *str, char **env)
{
	char	*res;

	res = repl_dlr(str, env, 0);
	if (res != str)
		free (str);
	del_quo(res, DQ);
	return (res);
}

char	*strip_quo(char *str, char **env, int fl_free)
{
	char	*tmp;

	tmp = str;
	if (str)
	{
		if (*tmp == SQ)
			tmp = replace_sq(str);
		else if (*tmp == DQ)
			tmp = replace_dq(str, env);
		else
			tmp = repl_dlr(str, env, (tmp != str));
		if (fl_free && (tmp != str))
			free(str);
}
	return (tmp);
}

void	del_quotes(char **arg, char **env)
{
	char	*tmp;

	if (arg)
		while (*arg)
		{
			tmp = *arg;
			del_empty_sp(*arg);
			*arg = strip_quo(*arg, env, (tmp != *arg));
			arg++;
		}
}

char	*repl_dlr(char *ptr, char **env, int fl_free)
{
	t_replace	r;
	char		*res;
	char		*tmp;
	char		*pos;
	char		*name;

	pos = get_pos_after(ptr, 0, DL);
	res = ptr;
	tmp = NULL;
	while (pos)
	{
		r = (t_replace){.src = res, .val = NULL, .st = pos - res, .len = 0};
		while (is_in_name(pos + r.len + 1))
			r.len++;
		if (r.len)
		{
			name = ft_substr(res + r.st, 1, r.len++);
			r.val = get_env_val(env, name);
			free (name);
			if (res != ptr)
			 	tmp = res;
			res = replace(&r);
			free (tmp);
			r.st += ft_strlen(r.val) - 1;
			free (r.val);
		}
		else
			r.st++;
		pos = get_pos_after(res, r.st, DL);
	}
	if (fl_free && (res != ptr))
		free(ptr);
	return (res);
}

/*
**	replace substr, values from struct r
**	--------------------------------------------
**	| * |...|   | * |   |...|   | * |   |...|\0|
**	  |			  |				  |
**	r.src	r.src + r.st	r.src + r.st + r.len
**				  \				  /
**					-------------
**			      replaced by r.val
*/

char	*replace(t_replace *r)
{
	char	*res;
	size_t	len_src;
	size_t	len_val;

	res = r->src;
	if (r->len >= 0 && r->val)
	{
		len_src = ft_strlen(r->src);
		len_val = ft_strlen(r->val);
		if ((r->st >= 0) && (r->st < (int)len_src) && \
					(r->len <= ((int)len_src - r->st)))
		{
			res = malloc(len_src - r->len + len_val + 1);
			if (res)
			{
				ft_strlcpy(res, r->src, r->st);
				ft_strlcpy(res + r->st, r->val, len_val);
				ft_strlcpy(res + r->st + len_val, r->src + r->st + r->len, \
							len_src - r->st - r->len);
			}
		}
	}
#ifdef NDEBUG
printf("repl: src("REDS") + val(%s) from(%i), len(%i) =[%i]=> res(%s)\n",  \
			r->src, r->val, r->st, r->len, (r->src == res), res);
#endif
	return (res);
}