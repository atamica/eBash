#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*d;
	char const	*s;

	if (dst && src)
	{
		d = (char *)(dst);
		s = (char *)(src);
		if (dst < src)
			while (n--)
				*d++ = *s++;
		if (src < dst)
			while (n--)
				d[n] = s[n];
	}
	return (dst);
}
