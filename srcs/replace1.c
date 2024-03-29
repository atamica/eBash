#include "minishell.h"

static	void	replace_r(t_replace *r, char *ptr, char **res, char **env)
{
	char		*name;
	char		*tmp;

	tmp = NULL;
	name = ft_substr(*res + r->st, 1, r->len++);
	r->val = get_env_val(env, name);
	free (name);
	if (*res != ptr)
		tmp = *res;
	*res = replace(r);
	free (tmp);
	r->st += ft_strlen(r->val) - 1;
	free (r->val);
}

char	*repl_dlr(char *ptr, char **env, int fl_free)
{
	t_replace	r;
	char		*res;
	char		*pos;

	pos = get_pos_char(ptr, DL);
	res = ptr;
	while (pos)
	{
		r = (t_replace){.src = res, .val = NULL, .st = pos - res, .len = 0};
		while (is_in_name(pos + r.len + 1))
			r.len++;
		if (r.len)
			replace_r(&r, ptr, &res, env);
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
**			      replaced on r.val
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
	return (res);
}

/*
char	*replace_star(t_d *d, char *str)
{
	char	*ptr;

	ptr = str;
	if (get_pos_char(str, '*'))
	{
		ptr = star_to_char(str, d);
		free(str);
	}
	return (ptr);
}
*/

/*
**	arg = arg.[begin, ..., pos) + b.[pos, ..., pos + len.b) + 
**									+ arg.[pos + len.b, ..., end]
*/

# if BONUS == 1

size_t	merge_args(t_d *d, char ***arg_ptr, size_t pos)
{
	size_t	res;
	size_t	len;
	size_t	i;
	char	**b;
	char	**tmp;

	b = star((*arg_ptr)[pos], d);
	res = amount_elements(b);
	len = res + amount_elements(*arg_ptr);
	free((*arg_ptr)[pos]);
	if (res)
	{
		if_err_fatal(tmp = malloc(sizeof(char *) * len), 2, d);
		i = 0;
		while (i + 1 < len)
		{
			if (i < pos)
				tmp[i] = (*arg_ptr)[i];
			else if (i < pos + res)
				tmp[i] = b[i - pos];
			else
				tmp[i] = (*arg_ptr)[i - res + 1];
			i++;
		}
		tmp[i] = NULL;
		free(*arg_ptr);
		*arg_ptr = tmp;
	}
	else
	{
		while (pos < len)
		{
			(*arg_ptr)[pos] =(*arg_ptr)[pos + 1];
			pos++;
		}
		free((*arg_ptr)[pos]);
	}
	free(b);
	return (res);
}

#endif
