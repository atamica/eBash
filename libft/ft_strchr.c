#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*d;
	unsigned char	cc;

	if (s)
	{
		d = (char *)s;
		cc = (unsigned char)c;
		while (*d)
		{
			if (*d == cc)
				return (d);
			d++;
		}
		if (!c)
			return (d);
	}
	return (NULL);
}
