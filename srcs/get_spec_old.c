#include "minishell.h"

/* char	*ft_get_spec_ch(char *str, char c)
{
	char *pos;
	int i;
	int j;
	char s_quote;
	char d_quote;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	pos = ft_strchr(str, c);
	if (!pos || (pos == str))
		return (pos);
	i = 0;
	while (str[i])
	{
		while (pos && *pos && *(pos - 1) == '\\')
			pos = ft_strchr(pos + 1, c);
		j = i;
		while (str[j] && str[j] != DQ && str[j] != SQ)
			j++;
		if (str[j] && str[j] == DQ)
			d_quote = 1;
		else if (str[j] && str[j] == SQ)
			s_quote = 1;
		if (str[j] && (str + j) > pos)
			return (pos);
		else if (str + j < pos)
		{	
			j++;
			if (d_quote)
			{
				while (str[j] && str[j] != DQ)
					j++;
				if (str[j] && (str + j) < pos)
					d_quote = 0;
				else if (str[j])
					pos = ft_strchr(str + j + 1, c);
			}
			else if (s_quote)
			{
				while (str[j] && str[j] != SQ)
					j++;
				if (str[j] && (str + j) < pos)
					s_quote = 0;
				else if (str[j])
					pos = ft_strchr(str + j + 1, c);
			}
		}
		if (str[j])
			i = j + 1;
		else 
			i = j;
	}
	return (pos);
}
 */