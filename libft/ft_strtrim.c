#include "libft.h"

/*
**	trim S1, from SET
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	l;

	if (s1 && set)
	{
		while (*s1 && ft_strchr(set, *s1))
			s1++;
		l = ft_strlen(s1);
		while (l && ft_strrchr(set, *(s1 + l - 1)))
			l--;
		return (ft_substr(s1, 0, l));
	}
	return (NULL);
}
