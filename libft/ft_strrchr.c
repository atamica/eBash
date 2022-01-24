#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			l;
	unsigned char	cc;

	if (s)
	{
		l = ft_strlen(s);
		if (!c)
			return ((char *)s + l);
		cc = (unsigned char)c;
		while (l)
		{
			if (s[l - 1] == cc)
				return ((char *)(s + l - 1));
			l--;
		}
	}
	return (NULL);
}
