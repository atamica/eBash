#include "minishell.h"

void	skip_sp(char *str, int *i, t_fl *fl)
{
	int	j;

	j = *i;
	while (ft_isalsp(*(str + j)) && !is_qu(fl))
		j++;
	*i = j;
}

int	parser(char *str, t_cmd *cmd)
{
	int		r;
	int		start;
	int		i;
	char	*ptr;
	t_fl	fl;

	r = 0;
	i = 0;
//	init_cmd(cmd);
	init_fl(&fl);
	if (str)
	{
// skip spases
		skip_sp(str, &i, &fl);
/* 		while (*(str + i) && ft_isalsp(*(str + i)))
			i++; */
// parse cmd
		start = i;
		while (*(str + i) && !ft_strchr(" ;\"\'$", *(str + i)))
			i++;
		if (i == start)
			ptr = MSG0;
		else
			ptr = ft_substr(str, start, i - start);
// try add path
		if (is_builtins(ptr)) // || (is_file_exist(ptr) == 1) 
			cmd->path = ft_strdup(ptr);
		else
			cmd->path = cmdf(ptr);
		cmd->type = type_cmd(ptr);
//printf("pars: path=%s type=%i\n", cmd->path, cmd->type);
		free_nu(ptr);
// parse options

// parse args
		cmd->arg = ft_split(str, ' ');

		if (cmd->path)
			r = 1;
		
		// parse "; | || & && >> << < >"
	}
	return (r);
}


int	pars(char *str, t_cmd *cmd)
{
	int		r;
	int		start;
	int		i;
	char	*ptr;
	t_fl	fl;

	r = 0;
	i = 0;
//	init_cmd(cmd);
	init_fl(&fl);
	if (str)
	{
// skip spases
		while (*(str + i) && ft_isalsp(*(str + i)))
			i++;
// parse cmd
		start = i;
		while (*(str + i) && !ft_strchr(" ;\"\'$", *(str + i)))
			i++;
		if (i == start)
			ptr = MSG0;
		else
			ptr = ft_substr(str, start, i - start);
// try add path
		if (is_builtins(ptr)) // || (is_file_exist(ptr) == 1) 
			cmd->path = ft_strdup(ptr);
		else
			cmd->path = cmdf(ptr);
		cmd->type = type_cmd(ptr);
//printf("pars: path=%s type=%i\n", cmd->path, cmd->type);
		free_nu(ptr);
// parse options

// parse args
		cmd->arg = ft_split(str, ' ');

		if (cmd->path)
			r = 1;
		
// parse "; | || & && >> << < >"
	}
	return (r);
}

void	set_flags(t_fl *fl, char c)
{
	if (c == SQ && !fl->fl_d_qu)
		fl->fl_s_qu = !fl->fl_s_qu;
	if (c == DQ && !fl->fl_s_qu)
		fl->fl_s_qu = !fl->fl_s_qu;
	if (c == DL && !fl->fl_s_qu)
		fl->fl_dol = !fl->fl_dol;
}


