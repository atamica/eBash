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

void	del_space(char *str)
{
	t_pos	r;
	char	*ptr;
	size_t	lsp;

	if (str)
	{
		ptr = str;
		while (*ptr)
		{
			if (ft_strchr(ALL_SP, *ptr))
			{
				r = fill_sp(ptr);
				lsp = ((ptr != str) && *r.end);
				if (lsp)
					*r.st++ = '@';
				if (r.len > lsp)
					while (*r.st)
						*r.st++ = *r.end++;
				ptr += lsp;
			}	
			else
				ptr += fill_no_sp(ptr).len;
		}
	}
}
