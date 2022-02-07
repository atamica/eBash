#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	res = 0;
	while (ft_isalsp(*str))
		str++;
	sign = 1 - ((*str == '-') << 1);
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		if (res * 10 < res)
			return (-(sign >= 0));
		res *= 10;
		res += *str++ - '0';
	}
	return (sign * res);
}
