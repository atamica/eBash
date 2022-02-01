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
	char	*ptr;

	ptr = str;
	if (str)
	{
		if (*ptr == SQ)
			ptr = replace_sq(str);
		else if (*ptr == DQ)
			ptr = replace_dq(str, env);
		else
		{
			ptr = repl_dlr(str, env, (ptr != str));
			if (fl_free && (ptr != str))
				free(str);
		}
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
			*arg = strip_quo(tmp, env, 1);
			arg++;
		}
	}
}
