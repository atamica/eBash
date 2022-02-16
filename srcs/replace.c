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

char	*strip_quo(char *str, char **env)
{
	char	*ptr;

	ptr = str;
	if (str)
	{
		if (*ptr == SQ)
			ptr = replace_sq(str);
		else if (*ptr == DQ)
			ptr = replace_dq(str, env);
	}
	return (ptr);
}

void	del_quotes(char **arg, char **env)
{
	char	*tmp;

	if (arg)
	{
		while (*arg)
		{
			tmp = *arg;
			del_empty_sp(*arg);
			*arg = strip_quo(tmp, env);
			arg++;
		}
	}
}

#if BONUS == 1
void	manager_replace(char ***arg, char **env, t_d *d)
{
	char	**tmp;

	size_t	pos;
	size_t	offs;

	if (*arg)
	{
		tmp = *arg;
		while (*tmp)
		{
			del_empty_sp(*tmp);
			*tmp = repl_dlr(*tmp, env, 1);
			if (is_present_non_screened_char(*tmp, '*'))
			{
				pos = tmp - *arg;
				offs = merge_args(d, arg, pos) + pos;
				tmp = *arg + offs;
				pos = tmp - *arg;
			}
			*tmp = strip_quo(*tmp, env);
			tmp++;
		}
	}
}
#else
void	manager_replace(char ***arg, char **env)
{
	char	**tmp;

	if (*arg)
	{
		tmp = *arg;
		while (*tmp)
		{
			del_empty_sp(*tmp);
			*tmp = repl_dlr(*tmp, env, 1);
			*tmp = strip_quo(*tmp, env);
			tmp++;
		}
	}
}
#endif
