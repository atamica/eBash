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

int	pars(char *str, t_cmd *cmd, t_d *d)
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
		//cmd->arg = ft_split(str, ' ');
		while (str[i] && ft_strchr(";&|<>", str[i]))
			i++;
		ptr = ft_substr(str, start, i - start);
		cmd->arg = ft_split(ptr, ' ');
		free_null((void **)&ptr);
/* 		if (i)
			i--; */
		if (cmd->path)
			r = 1;
		clear_pipes(d);
		while (str[i] && !ft_strchr(" ;&|<>", str[i]))
		{
			if (str[i] == '>')
			{
				if (str[i + 1] && str[i + 1] == '>')
				{
					d->out2redir = 1;
					i++;
				}
				else d->outredir = 1;
			}
			else if (str[i] == '<')
			{
				if (str[i + 1] && str[i + 1] == '<')
				{
					d->in2redir = 1;
					i++;
				}
				else d->inredir = 1;
			}
			else if (str[i] == '|')
			{
				if (str[i + 1] && str[i + 1] != '|')
				{
					d->double_pipe = 1;
					i++;
				}
				else d->pipe = 1;
			}
			else if (str[i] == '&')
			{
				if (str[i + 1] && str[i + 1] == '&')
				{
					d->double_and = 1;
					i++;
				}
			}
			i++;
		}
		str += i;
		// parse options
		// parse args
		// parse "; | || & && >> << < >"
	}
	return (r);
}