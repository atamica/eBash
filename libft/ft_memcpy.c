#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (dest && src)
		while (n--)
			*(char *)dest++ = *(char *)src++;
	return (dest);
}
