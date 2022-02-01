#include "minishell.h"

int	is_only_digits(char *str)
{
	int	r;

	r = 0;
	if (str)
	{
		if (*str == '-' || *str == '+')
			str++;
		r = ft_isdigit(*str);
		while (*str)
		{
			if (!ft_isdigit(*str))
				return (0);
			str++;
		}
	}
	return (r);
}

int	is_in_name(char *str)
{
	return ((*(str) == '_') || ft_isalnum(*(str)));
}

int	is_in_fname(char c)
{
	return((c == '.') || (c == '_') || (c == SL) || ft_isalnum(c));
}
