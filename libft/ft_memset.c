#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*b1;
	unsigned char	cc;

	b1 = b;
	cc = (unsigned char)c;
	while (len--)
		*b1++ = cc;
	return (b);
}
