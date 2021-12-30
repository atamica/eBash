#include "minishell.h"

int	main(int ac, char **av, char **env)
{

	int		status = 1;
//	char	*tmp;
//	char	*tm;
//	char	**tok;
	t_d		d;
	t_cmds	*cmds;
	int		i;

	init_start(&d, ac, av, env);
/* 	buf = NULL;
	fd = add_to_hist_file("minishell_history"); */
	while (status)
	{
		d.input = readline(prompt(&d));
		free(d.prompt);
		d.fr = 1;
		if (!d.input)
		{
			status = 0;
			break ;
		}
		/* if (d.input[0] == 'a')
			rl_redisplay(); */

		// path autocompletion when tabulation hit
		//rl_bind_key('\t', rl_complete);

		// adding the previous input into history
/*printf("---------------------------------------------------\n");		
printf("rl:(%s) point=%i end=%i\n", rl_line_buffer, rl_point, rl_end);
printf("rl:terminal(%s) name=%s\n", rl_terminal_name, rl_readline_name); */

		add_history(d.input);
/* 		buf = ft_strjoin(d.input, "\n");
		ft_putstr_fd(buf, fd);
		free(buf); */
/*printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
printf("qu:(%s) (%s)\n", in_quotes(d.input, '"'), in_quotes(d.input, '\''));
		tmp = dollar(d.input, &d);
		 if (tmp)
			{
			free(d.input);
			d.input = tmp;
printf("$: (%s)\n", tmp);
		} */
//		pars(d.input, &d.cmd);

// parser(d.input, &d.cmd);
// printf("pars: ret=%i (%s)\n", pars(d.input, &d.cmd, &d), d.input);
// printf("cmd=(%s) dir=%i file=%i type=%i\n", d.cmd.path, is_dir(d.cmd.path), \
// 		is_file_exist(d.cmd.path), d.cmd.type);

/*
printf("args=");
print_param(d.cmd.arg, " ", ' ');
printf(N);
printf("redir: %i\n", find_redir(d.input));
printf("spec: (%s) [%s]\n", d.input, ft_get_spec_ch(d.input, L));
*/
//printf("filenames: (%s) ret=%i fd:0(%i) 1(%i)\n", d.input, get_fd(d.input, &d, &d.cmd), d.cmd.fd[0], d.cmd.fd[1]);
/*  
tok  = split_cmds(&d);
printf("get_tok: |");
print_param(tok, "", '&');
free2(tok);
printf(N);*/
// tm = replace_dq(ft_strdup(d.input), &d);
// printf("repl_dq: (%s) - (%s)\n", d.input, tm);
// free (tm);
// tm = repl_d(d.input, &d);
// printf("$: (%s) - (%s)\n", d.input, tm);
// free (tm);
//printf("gpc: (%s)\n", get_pos_char(d.input, DL));
cmds = pa2(&d);
//d.cmd = *cmds[0].cmd;
i = -1;
while (++i < cmds->count)
	printf("%2i. str(%s) type(%i)\n", i, cmds->cmd[i].path,  cmds->cmd[i].type);
// assert(1);
printf("===================================================\n");
/* 		d.cmd.env = d.env;
		if (d.cmd.path && (d.cmd.type == EXTERNALS))
			d.stat = cmd0(&d);\
		else
			d.stat = run_builtins(&d);
printf("___________________________________________________\n"); */
i = -1;
d.stat = 0;
while ((++i < cmds->count) && !d.stat)
{
//	d.cmd = *cmds[i].cmd;
//print_param(d.cmd.arg, "st:", ':');
//	cmds[i].cmd->env = d.cmd.env;
	if (i < cmds->count)
	{
		// create pipe
		if_err_exit(pipe(cmds->cmd[i].fd), 3, &d);
	}
	if (cmds->cmd[i].type == EXTERNALS)
		d.stat = cmd_cmd(&d, cmds->cmd + i);
	else if (cmds->cmd[i].type == BUILTINS)
		d.stat = run_builtins_cmd(&d, cmds->cmd + i);
	printf("~~~~~~~~~~~~~~~~~~~~ code_ret(%i)\n", d.stat);
}
/* d.stat = run(d.input); */
free_cmds(cmds);
printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		init_cmd_free(&d.cmd);
		free(d.input);
		close_f2(d.cmd.fd);
	}
	printf(N);
	free_d(&d);
	return (0);
}
