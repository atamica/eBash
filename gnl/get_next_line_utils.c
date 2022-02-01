#include "get_next_line.h"

char	*ft_strdup_mod(char **s, int del)
{
	char	*r;
	size_t	l;

	l = ft_strlen(*s) + 1;
	r = (char *)malloc(l * sizeof(char));
	if (r)
	{
		ft_strlcpy(r, *s, l);
		if (del && *s)
		{
			free(*s);
			*s = NULL;
		}
		return (r);
	}
	return (NULL);
}

char	*ft_strjoin_mod(char **s1, char *s2)
{
	char	*r;
	size_t	l1;
	size_t	l2;

	if (*s1 && s2)
	{
		l1 = ft_strlen(*s1);
		l2 = ft_strlen(s2) + 1;
		if ((r = (char *)malloc((l1 + l2) * sizeof(char))))
		{
			ft_strlcpy(r, *s1, l1 + 1);
			ft_strlcpy(r + l1, s2, l2);
			free(*s1);
			*s1 = NULL;
			return (r);
		}
	}
	if (*s1)
		return (ft_strdup_mod(s1, 1));
	if (s2)
		return (ft_strdup_mod(&s2, 0));
	return (NULL);
}
