#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	r;
	size_t	len_word;

	r = 0;
	while (*s)
	{
		len_word = 0;
		while (*s && (*s != c))
		{
			len_word++;
			s++;
		}
		if (len_word)
			r++;
		if (*s)
			s++;
	}
	return (r);
}

static size_t	len_word(char const *s, char c, size_t *n)
{
	size_t	i;
	size_t	l;
	char	f;

	i = 0;
	*n = 0;
	while (s[i])
	{
		l = 0;
		f = 1;
		while (s[i] && (s[i] != c))
		{
			if (f)
			{
				*n = i;
				f = 0;
			}
			l++;
			i++;
		}
		if (l)
			return (l);
		i++;
	}
	return (0);
}

static char	**mlc(char **rt, char const *s, size_t words_count, char c)
{
	size_t	i;
	size_t	l;
	size_t	n;

	rt[words_count] = NULL;
	i = -1;
	while (words_count--)
	{
		l = len_word(s, c, &n);
		rt[++i] = (char *)malloc((l + 1) * sizeof(char));
		if (rt[i])
		{
			s += n;
			ft_strlcpy(rt[i], s, l);
			s += l;
		}
		else
		{
			while (i)
				free(rt[--i]);
			free(rt);
			return (NULL);
		}
	}
	return (rt);
}

char	**ft_split(char const *s, char c)
{
	size_t	words_count;
	char	**rt;

	if (s)
	{
		words_count = count_words(s, c);
		rt = (char **)malloc((words_count + 1) * (sizeof(char *)));
		if (rt)
			return (mlc(rt, s, words_count, c));
	}
	return (NULL);
}
