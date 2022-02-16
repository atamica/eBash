#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	size_t	len_lit;
	size_t	len_big;
	size_t	len_rest;

	if (big && lit)
	{
		len_lit = ft_strlen(lit);
		if (!len_lit)
			return ((char *)big);
		if (len > len_lit)
			len = len_lit;
		len_big = ft_strlen(big);
		if (len_big >= len)
		{
			len_rest = 1 + len_big - len;
			while (*big && len_rest--)
			{
				if (!ft_memcmp(big, lit, len))
					return ((char *)(big));
				big++;
			}
		}
	}
	return (NULL);
}
