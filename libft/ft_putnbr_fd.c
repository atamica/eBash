#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	a;
	int	z;
	int	tmp;

	a = 1;
	z = 1;
	tmp = n;
	while (tmp)
	{
		tmp /= 10;
		a *= 10;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		z = -1;
	}
	while (a)
	{
		ft_putchar_fd('0' + z * (n / a), fd);
		n %= a;
		a /= 10;
	}
}
