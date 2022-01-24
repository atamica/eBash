#include "libft.h"

int	ft_isalsp(char c)
{
	return ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\v') || \
			(c == '\f') || (c == '\r'));
}
