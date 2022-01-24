#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*r;
	size_t	l;

	if (s && f)
	{
		l = ft_strlen(s);
		r = (char *)malloc((l + 1) * sizeof(char));
		if (r)
		{
			l = 0;
			while (s[l])
			{
				*(r + l) = f((unsigned int)l, *(s + l));
				l++;
			}
			*(r + l) = 0;
			return (r);
		}
	}
	return (NULL);
}
