#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_std_lib.h"
# include "minishell_consts.h"
# include "minishell_structs.h"
# include "libft.h"
# include "get_next_line.h"

/*
**		run.c
*/

# ifdef NDEBUG_RUN

int			run(t_d *d);

# endif

int			cmd_cmd(t_d *d, t_cmd *cmd, int *pipe_in, int *pipe_out);

/*
**		parser.c
*/

int			parser(char *str, t_cmd *cmd, t_d *d);
int			parser(char *str, t_cmd *cmd, t_d *d);
int			pars(char *str, t_cmd *cmd, t_d *d);

/*
**		utils.c
*/

char		*ft_strjoin_c(char const *s1, char const *s2, char c);
char		*add_path(char *cmd);
void		dup2_check(int old_fd, int new_fd, t_d *d);
void		dup_io(int *fd, t_d *d, int *pipe_in, int *pipe_out);

size_t		sp_count(char *ptr);
char		*skip_spaces(char *ptr);
char		*skip_not_spaces(char *ptr);
void		print_param(char **arg, char *prefix, char separator);
void		print_param_fd(char **arg, char *prefix, char separator, int fd);

void		del_empty_sp(char *str);
void		del_substring(char *start, size_t len);
void		check_opened_fd(void);

char		*get_pos_char(char *str, char c);
char		*get_pos_after(char *str, int offset, char c);
char		*prompt(t_d *d);
size_t		amount_elements(char **ptr);

size_t		ft_lstcalc_total_len(t_list *lst);

/*
**		err.c
*/

void		err_msg(char *msg, int code, t_d *d);
char		*msg_error(int code);
void		err(int code, t_d *d);
void		if_err_exit(int er, int code, t_d *d);
int			out_msg(char *msg, int code);
void		if_err_fatal(void *ptr, int code, t_d *d);
int			syntax_err(char c);
void		if_err_no_fatal(int er, int code, t_d *d);
int			err_open(int fd, t_d *d);
void		if_err_cd(int er, int fd, char *path);

/*
**		close.c
*/

void		close_f(int fd);
void		close_f2(int *fd);
void		close_f3(int *fd);
void		close_f2any(int *fd);
void		close_f3any(int *fd);
void		close_files_rd(t_cmd *cmd);
void		close_if(t_fout fout);

/*
**		free.c
*/

void		free_null(void **ptr);
void		free2(char **ptr);
void		free_d(t_d *d);
void		free_cmd(t_cmd *cmd);
void		free_cmds(t_cmds *cmds);

/*
**		builtins/ *.c
*/

int			ft_cd(t_cmd *cmd);
int			ft_echo(t_cmd *cmd, int fd);
int			ft_pwd(t_cmd *cmd);
int			ft_env(t_d *d, int fd);
int			ft_export(t_d *d, int fd, char **args, char **env);
int			ft_exit(t_cmd *cmd, t_d *d);
int			ft_unset(t_d *d, char **args);

int			type_cmd(char *cmd);
void		set_env_val(char *name, char *val, t_d *d);
char		*get_env_val(char **env, char *name);
int			copy_envs(char **env_ex, t_d *d);
int			len_env_list(char **env);
int			run_builtins_cmd(t_d *d, t_cmd *cmd, int *pipe_out);

/*
**		init.c
*/

void		init_cmd(t_cmd *cmd);
void		init_start(t_d *d, int ac, char **av, char **env);

/*
**		is.c
*/

int			is_builtins(char *cmd);
int			is_ext_cmd(char *cmd);
int			is_dir(char *path);
int			is_file_exist(char *path);
t_val		is_in_env_list(char **env, char *name);
int			is_only_digits(char *str);
int			is_in_name(char *str);
int			is_char_valid_fname(char c);
int			is_in_quo(char *str);
int			is_present_non_screened_char(char *str, char c);

/*
**		history.c
*/

int			add_to_hist_file(const char *f_name);

/*
**		heredoc.c
*/

void		h_doc(int fd, t_cmd *cmd, t_d *d);
void		prepare_hdoc_pipe(t_cmd *cmd, t_d *d, int *pipe_in);

/*
**		redirections/ *
*/

int			err_open(int fd, t_d *d);
char		*filename(char *ptr);
int			find_redir(char *str);
int			get_fd(char *str, t_d *d, t_cmd *cmd);
int			rd_s_left(char *str, t_cmd *cmd, t_d *d);
int			rd_d_left(char *str, t_cmd *cmd);
int			rd_s_right(char *str, t_cmd *cmd, t_d *d);
int			rd_d_right(char *str, t_cmd *cmd, t_d *d);
void		restore_std_io(t_d *d);

/*
**		par.c
*/

int			pipes_count(char *str);
char		*skip_sps(char *ptr);
t_splits	*split_cmds2(t_d *d);
t_cmds		*pa2(t_d *d);

/*
**		replace.c
*/

void		del_quo(char *str, char c);
char		*replace_sq(char *str);
char		*replace_dq(char *str, char **env);
void		del_quotes(char **arg, char **env);
char		*repl_dlr(char *ptr, char **env, int fl_free);
char		*replace(t_replace *r);
char		*strip_quo(char *str, char **env);
//char		*replace_star(t_d *d, char *str);
void		manager_replace(char ***arg, char **env, t_d *d);
size_t		merge_args(t_d *d, char ***arg_ptr, size_t pos);

/*
**		srcs/signals.c
*/

void		my_handler(int signo);
void		init_signals(t_d *d);

/*
**		star.c
*/

char		**star(char *str, t_d *d);
//char		*star_to_char(char *str, t_d *d);

#endif
