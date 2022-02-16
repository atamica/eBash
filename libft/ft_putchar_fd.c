#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
#ifdef OPTIM
	if (write(fd, &c, sizeof(c)))
	{
		;
	}
#else
	write(fd, &c, sizeof(c));
#endif
}
