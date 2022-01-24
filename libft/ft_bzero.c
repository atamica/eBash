#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*b;

	if (s && n)
	{
		b = (char *)s;
		while (n--)
			*b++ = 0;
	}
}
