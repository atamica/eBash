#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	len;
	void	*r;

	len = nmemb * size;
	r = (void *)malloc(len);
	if (r)
		ft_bzero(r, len);
	return (r);
}
