#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	l;

	l = 0;
	if (dst)
	{
		while (src && size-- && *src)
		{
			*dst++ = *src++;
			l++;
		}
		*dst = 0;
	}
	return (l);
}
