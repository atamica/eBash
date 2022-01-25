#include "minishell.h"

char	*get_pos_char(char *str, char c)
{
	int	fl_sq;
	int	fl_dq;

	fl_dq = 1;
	fl_sq = 1;
	if (str)
	{
		while (*str)
		{
			if ((*str == SQ) && fl_dq)
				fl_sq = !fl_sq;
			else if ((*str == DQ) && fl_sq)
				fl_dq = !fl_dq;
			else if (((*str == c) && fl_sq && fl_dq) || \
						((*str == c) && (c == DL) && fl_sq))
				return (str);
			str++;
		}
	}
	return (NULL);
}
