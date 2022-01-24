#include "libft.h"

int	ft_atoi(const char *str)
{
	int	z;
	int	r;

	z = 1;
	r = 0;
	while (ft_isalsp(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			z = -1;
	while (ft_isdigit(*str))
	{
		if (r * 10 < r)
			return (-(z >= 0));
		r *= 10;
		r += *str++ - '0';
	}
	return (z * r);
}
