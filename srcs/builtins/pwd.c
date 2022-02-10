#include "minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*tmp;

	tmp = malloc(LEN_PATH);
	if (tmp)
	{
		ft_putendl_fd(getcwd(tmp, LEN_PATH), cmd->fd[1]);
		free(tmp);
	}
	return ((tmp == NULL) << 1);
}
