#include "minishell.h"

int	ft_pwd(void)
{
	char	*tmp;

	tmp = malloc(LEN_PATH);
	if (tmp)
	{
		printf("%s\n", getcwd(tmp, LEN_PATH));
		free(tmp);
		return (0);
	}
	return (2);
}
