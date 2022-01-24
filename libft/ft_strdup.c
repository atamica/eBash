#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*r;
	size_t	l;

	l = ft_strlen(s);
	r = (char *)malloc((l + 1) * sizeof(char));
	if (r)
		ft_strlcpy(r, s, l);
	return (r);
}
