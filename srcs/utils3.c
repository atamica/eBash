#include "minishell.h"

char	*get_pos_char(char *str, char c)
{
	int	fl_sq;
	int	fl_dq;

	fl_dq = 1;
	fl_sq = 1;
	if (str)
	{
		while (*str)
		{
			if ((*str == SQ) && fl_dq)
				fl_sq = !fl_sq;
			else if ((*str == DQ) && fl_sq)
				fl_dq = !fl_dq;
			else if (((*str == c) && fl_sq && fl_dq) || \
						((*str == c) && (c == DL) && fl_sq))
				return (str);
			str++;
		}
	}
	return (NULL);
}

/*
**	find non sreened char c in string str after offset bytes
**	return first position c in str, or NULL if result find == 0, or str == NULL.
*/

char	*get_pos_after(char *str, int offset, char c)
{
	int		fl_sq;
	int		fl_dq;
	char	*st;

	fl_dq = 1;
	fl_sq = 1;
	st = str;
	if (str)
	{
		while (*str)
		{
			if ((*str == SQ) && fl_dq)
				fl_sq = !fl_sq;
			else if ((*str == DQ) && fl_sq)
				fl_dq = !fl_dq;
			else if ((((*str == c) && fl_sq && fl_dq) || \
						((*str == c) && (c == DL) && fl_sq)) && \
						((str - st) > offset))
				return (str);
			str++;
		}
	}
	return (NULL);
}

static size_t	add_str(char *ptr, char *str, size_t offset)
{
	size_t	len;

	len = ft_strlen(str);
	ft_memcpy(ptr + offset, str, len);
	return (len);
}

char	*prompt(t_d *d)
{
	char	*user;
	char	*path;
	char	p[LEN_PATH];
	size_t	len;

	user = get_env_val(d->env, "USER");
	path = getcwd(p, LEN_PATH);
	len = ft_strlen(GREEN) + ft_strlen(user) + ft_strlen(RESET) + \
			ft_strlen(BLUE) + ft_strlen(path) + ft_strlen(RESET) + 3;
	if_err_fatal(d->prompt = (char *)malloc(len), 2, d);
	len = add_str(d->prompt, GREEN, 0);
	len += add_str(d->prompt, user, len);
	free(user);
	len += add_str(d->prompt, RESET, len);
	*(d->prompt + len++) = ':';
	len += add_str(d->prompt, BLUE, len);
	len += add_str(d->prompt, path, len);
	len += add_str(d->prompt, RESET, len);
	ft_memcpy(d->prompt + len, "$", 2);
	return (d->prompt);
}

size_t	amount_elements(char **ptr)
{
	size_t	amount;

	amount = 0;
	while (ptr && *ptr++)
		amount++;
	return (amount);
}

size_t	ft_lstcalc_total_len(t_list *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		len += ft_strlen((const char *)lst->content) + 1;
		lst = lst->next;
	}
	return (len);
}

char	*get_current_dir(void)
{
	char	*cur_dir;

	cur_dir = malloc(LEN_PATH);
	if (cur_dir && getcwd(cur_dir, LEN_PATH))
		return (cur_dir);
	free(cur_dir);
	return (NULL);
}
