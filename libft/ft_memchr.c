#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	c0;

	if (s)
	{
		c0 = (char)c;
		while (n--)
		{
			if (*(char *)s == c0)
				return ((void *)(s));
			s++;
		}
	}
	return (NULL);
}
