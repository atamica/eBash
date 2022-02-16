#include "minishell.h"

static void	cmd_fill(t_splits *tmp, t_cmds *cm, t_d *d)
{
	int	i;

	i = -1;
	while (tmp->cmds[++i])
	{
		init_cmd(cm->cmd + i);
		cm->cmd[i].env = d->env;
		cm->cod += parser(tmp->cmds[i], cm->cmd + i, d);
	}
	cm->cmd[i].type = EMPTY;
}

t_cmds	*create_array_cmds(t_d *d)
{
	t_cmds		*cm;
	int			i;
	t_splits	*tmp;

	if_err_fatal(cm = malloc(sizeof(t_cmds)), 2, d);
	*cm = (t_cmds){.d = d, .cod = 0, .count = 0, .cmd = NULL};
	tmp = split_cmds2(d);
	if (*tmp->cmds)
	{
		cm->count = tmp->amount;
		cm->pipes_count = cm->count - 1;
		if (cm->pipes_count > 0)
		{
			if_err_fatal(cm->fdp = malloc(sizeof(int *) * (cm->pipes_count)), \
																		2, d);
			i = -1;
			while (++i < cm->pipes_count)
				if_err_fatal(cm->fdp[i] = malloc(sizeof(int) * 2), 2, d);
		}
		if_err_fatal(cm->cmd = malloc(sizeof(t_cmd) * (cm->count + 1)), 2, d);
		cmd_fill(tmp, cm, d);
		free2(tmp->cmds);
		free(tmp);
	}
	return (cm);
}

int	pipes_count(char *str)
{
	int		l;
	char	*ptr;

	l = 0;
	if (str && *str)
	{
		ptr = get_pos_char(str, P);
		while (ptr++)
		{
			ptr = get_pos_char(ptr, P);
			l++;
		}
	}
	return (l);
}

/*
**	split by '|'
**	need add also split by other: ';', "&&" "||" for bonus
*/

t_splits	*split_cmds2(t_d *d)
{
	t_tk		t;
	t_splits	*res;

	if_err_fatal(res = malloc(sizeof(t_splits)), 2, d);
	t = (t_tk){.j = 0, .pips = pipes_count(d->input), .st = d->input};
	res->amount = 0;
	if (t.st)
	{
		res->amount = t.pips + 1;
		if_err_fatal(res->cmds = malloc(sizeof(char *) * (t.pips + 2)), 2, d);
		while (t.pips--)
		{
			t.end = get_pos_char(t.st, P);
			res->cmds[t.j++] = ft_substr(t.st, 0, t.end - t.st);
			t.st = t.end + 1;
		}
		res->cmds[t.j++] = ft_substr(t.st, 0, ft_strlen(t.st));
	}
	res->cmds[t.j] = NULL;
	return (res);
}
