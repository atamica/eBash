#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	int		status = 1;
//	char	*tmp;
	char	*tm;
//	char	**tok;
	t_d		d;

	init_start(&d, ac, av, env);
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
/*printf("---------------------------------------------------\n");		
 printf("rl:(%s) point=%i end=%i\n", rl_line_buffer, rl_point, rl_end);
printf("rl:terminal(%s) name=%s\n", rl_terminal_name, rl_readline_name); */
		add_history(d.input);
/*printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
printf("qu:(%s) (%s)\n", in_quotes(d.input, '"'), in_quotes(d.input, '\''));
		tmp = dollar(d.input, &d);
		 if (tmp)
			{
			free(d.input);
			d.input = tmp;
printf("$: (%s)\n", tmp);
		} */
		pars(d.input, &d.cmd);
/* printf("pars: ret=%i (%s)\n", pars(d.input, &d.cmd), d.input);
printf("cmd=(%s) dir=%i file=%i type=%i\n", d.cmd.path, is_dir(d.cmd.path), \
		is_file_exist(d.cmd.path), d.cmd.type);
printf("args=");
print_param(d.cmd.arg, " ", ' ');
printf(N); */
printf("redir: %i\n", find_redir(d.input));
//printf("spec: (%s) [%s]\n", d.input, ft_get_spec_ch(d.input, L));
//printf("filenames: (%s) ret=%i fd:0(%i) 1(%i)\n", d.input, get_fd(d.input, &d, &d.cmd), d.cmd.fd[0], d.cmd.fd[1]);
/* tok  = ft_get_tokens(d.input);
printf("get_tok: |");
print_param(tok, "", P);
free2(tok); */
printf(N);
tm = replace_sq(d.input);
printf("repl_sq: (%s) - (%s)\n", d.input, tm);
printf("$: (%s) - (%s)\n", d.input, repl_dl(d.input, &d));
//free (tm);
printf("===================================================\n");
/* while (1)
{}; */
		d.cmd.env = d.env_in;
		if (d.cmd.path && (d.cmd.type == EXTERNALS))
			d.stat = cmd0(&d);
		else
			d.stat = run_builtins(&d);
		init_cmd(&d.cmd);
		free(d.input);
		if (d.cmd.fd[0] > 2)
			close(d.cmd.fd[0]);
		if (d.cmd.fd[1] > 2)
			close(d.cmd.fd[1]);
	}
	printf(N);
	free_d(&d);
	return (0);
}
