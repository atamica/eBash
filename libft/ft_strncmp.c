#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	d;

	d = 0;
	if (s1 && s2 && n)
	{
		while ((unsigned char)*s1 && (unsigned char)*s2 && n--)
		{
			d = (unsigned char)*s1++ - (unsigned char)*s2++;
			if (d || !n)
				return (d);
		}
		return ((unsigned char)*s1 - (unsigned char)*s2);
	}
	return (d);
}
