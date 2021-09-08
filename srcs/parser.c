#include "minishell.h"

void	parser(char *input, t_cmd *cmd)
{
	char	**tmp;

	tmp = ft_split(input, ' ');
	if (tmp)
	{
		cmd->path = *tmp;
		cmd->arg = tmp;
	}
	else
	{
		cmd->path = NULL;
		cmd->arg = NULL;
	}
}

int	pars(char *str, t_cmd *cmd)
{
	int		r;
	int		start;
	int		i;
	char	*ptr;

	r = 0;
	i = 0;
	if (str)
	{
		// skip spases
		while (str[i] && ft_isalsp(str[i]))
			i++;
		// parse cmd
		start = i;
		while (str[i] && !ft_strchr(" ;&|<>", str[i]))
			i++;
		ptr = ft_substr(str, start, i - start);
		// try add path
		cmd->path = cmdf(ptr);
printf("path=%s\n", cmd->path);
		free_null((void **)&ptr);
		cmd->arg = ft_split(str, ' ');
		if (cmd->path)
			r = 1;
		// parse options
		// parse args
		// parse "; | || & && >> << < >"
	}
	return (r);
}