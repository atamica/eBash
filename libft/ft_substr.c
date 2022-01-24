#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	l;

	r = NULL;
	if (s)
	{
		l = ft_strlen(s);
		if (start > l)
			start = l;
		if (l < len + start)
			len = l - start;
		r = ft_calloc(len + 1, sizeof(char));
		if (r)
			ft_strlcpy(r, s + start, len);
	}
	return (r);
}
