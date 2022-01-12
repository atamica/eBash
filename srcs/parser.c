#include "minishell.h"

/* static void	skip_sp(char *str, int *i, t_fl *fl)
{
	int	j;

	j = *i;
	while (ft_isalsp(*(str + j)) && !is_qu(fl))
		j++;
	*i = j;
} */

int	parser(char *str, t_cmd *cmd)
{
	int		r;
	int		start;
	int		i;
	char	*ptr;
	t_fl	fl;

	r = 0;
	i = 0;
	init_cmd0(cmd);
	init_fl(&fl);
	if (str)
	{
		del_empty_sp(str);
// skip spases
//		skip_sp(str, &i, &fl);
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
		free(ptr);
// parse options

// parse args
		cmd->arg = ft_split(str, ' ');
print_param(cmd->arg,"parser:", ':');
printf(N);
		if (cmd->path)
			r = 1;
		
		// parse "; | || & && >> << < >"
	}
	return (r);
}

int	pars(char *str, t_cmd *cmd, t_d *d)

{
	int		r;
	int		start;
	int		i;
	char	*ptr;
	t_fl	fl;

	r = 0;
	i = 0;
	init_cmd0(cmd);
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
//		clear_pipes(d);
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
    
/*		if (i == start)
			ptr = MSG0;
		else
			ptr = ft_substr(str, start, i - start);
//printf("pars: ptr=(%s)\n", ptr);
// try add path
		if (is_builtins(ptr)) // || (is_file_exist(ptr) == 1) 
			cmd->path = ft_strdup(ptr);
		else
			cmd->path = cmdf(ptr);
		cmd->type = type_cmd(ptr);
//printf("pars: path=%s type=%i\n", cmd->path, cmd->type);
		free(ptr);
// parse options

// parse args
		cmd->arg = ft_split(str, ' ');

		if (cmd->path)
			r = 1;
		
// parse "; | || & && >> << < >"
*/
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

//		******************************** parcer ********************************

int	parsing_cmd(t_cmd *cmd, t_d *d)
{
	int			r;
	int			rd;
	t_replace	what_del;

	r = SUCCSESS;
	what_del = (t_replace){.src = cmd->str, .len = 0, .st = 0, .val = MSG0};
	if (cmd->str)
	{
		del_empty_sp(cmd->str);
		// redirections
		if ((rd = find_redir(cmd->str)) > 0)
		{
			// open f's 
			// char	*replace_d(t_replace *r)
			// find & cut
			r = get_fd(what_del.src, d, cmd);
		}
		if (rd < 0 || ((rd & S_LEFT) && (rd & D_LEFT)) || \
						((rd & S_RIGHT) && (rd & D_RIGHT)))
			return (ERROR);
	}
	return (r);
}
