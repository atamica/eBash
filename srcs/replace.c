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
