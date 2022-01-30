#include "minishell.h"

/*
**	delite quotes c = {", '} from begin and end of str
**	free old str, 
**	return new str if old str was stripped, else ptr on old str
*/

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

char	*replace_dq(char *str, char **env)
{
	char	*tmp;

	tmp = str;
	str = repl_dlr(str, env);
	if (tmp != str)
		free(tmp);
	tmp = str;
	str = replace_q(str, DQ);
	return (str);
}

void	del_quotes(char **arg, char **env)
{
	char	*tmp;

	if (arg)
		while (*arg)
		{
			del_empty_sp(*arg);
			tmp = *arg;
			if (*tmp == SQ)
				*arg = replace_sq(*arg);
			else if (*tmp == DQ)
				*arg = replace_dq(*arg, env);
			else
			{
				*arg = repl_dlr(*arg, env);
				if (tmp != *arg)
					free(tmp);
			}
			arg++;
		}
}

char	*repl_dlr(char *ptr, char **env)
{
	t_replace	r;
	char		*res;
	char		*pos;
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
			r.val = get_env_val(env, name);
			free (name);
 			if (res != ptr)
				free (res);
			res = replace_d(&r);
			r.st += ft_strlen(r.val) - r.len - 1;
			free (r.val);
		}
		else
			r.st++;
		pos = get_pos_char(res + r.st, DL);
	}
	return (res);
}

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
}