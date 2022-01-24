#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	l;
	size_t	r;

	l = 0;
	while (dst[l])
		l++;
	if (size < l)
		r = size + ft_strlen(src);
	else
		r = l + ft_strlen(src);
	while ((size > l + 1) && *src)
		dst[l++] = *src++;
	dst[l] = '\0';
	return (r);
}
