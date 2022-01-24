#include "minishell.h"

static t_pos	fill_sp(char *ptr)
{
	size_t	len;

	len = sp_count(ptr);
	return ((t_pos){.st = ptr, .end = ptr + len, .len = len});
}

static t_pos	fill_no_sp(char *ptr)
{
	size_t	len;
	size_t	min;
	char	*sp;
	char	*s;

	min = ft_strlen(ptr);
	sp = ALL_SP;
	while (*sp)
	{
		s = get_pos_char(ptr, *sp++);
		if (s)
		{
			len = s - ptr;
			if (min > len)
				min = len;
		}
	}	
	return ((t_pos){.st = ptr, .end = ptr + min, .len = min});
}

/*
**	function removes non-significant characters {' ', '\t',...  } = ALL_SP
**	spaces enclosed in quotation marks are preserved.
*/

void	del_empty_sp(char *str)
{
	t_pos	r;
	char	*ptr;
	size_t	leave_sp;

	if (str)
	{
		ptr = str;
		while (*ptr)
		{
			if (ft_strchr(ALL_SP, *ptr))
			{
				r = fill_sp(ptr);
				leave_sp = ((ptr != str) && *r.end);
				if (leave_sp)
					*r.st++ = SP;
				if (r.len > leave_sp)
					while (*r.st)
						*r.st++ = *r.end++;
				ptr += leave_sp;
			}	
			else
				ptr += fill_no_sp(ptr).len;
		}
	}
}

void	del_substring(char *start, size_t len)
{
	int		delta;
	
	if (start && len)
	{
		delta = ft_strlen(start) - len;
		if (delta > 0)
			ft_memmove(start, start + len, delta + 1);	// ft_bzero((void *)(start + delta), len);
		else
			*start = '\0';	// ft_bzero((void *)start, l_str);
	}
}
