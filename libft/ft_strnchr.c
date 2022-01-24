#include "libft.h"

char	*ft_strnchr(const char *s, int c, size_t n)
{
	char	*r;
	char	cc;

	r = (void *)(0);
	cc = (unsigned char)c;
	while ((n--) && (*s))
	{
		if (*s == cc)
			r = (char *)s;
		s++;
	}
	return (r);
}
