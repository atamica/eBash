#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	cmp;

	while (n--)
	{
		cmp = *((unsigned char *)(s1++)) - *((unsigned char *)(s2++));
		if (cmp)
			return (cmp);
	}
	return (0);
}
