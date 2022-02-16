#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
#ifdef OPTIM
	if (write(fd, s, ft_strlen((const char *)s)))
	{
		;
	}
#else
	write(fd, s, ft_strlen((const char *)s));
#endif
}
