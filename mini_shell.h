/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:33:45 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/19 16:40:13 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include <string.h>

# define TOKEN_ERROR -1
# define TOKEN_CMD 0
# define TOKEN_ARG 1
# define TOKEN_OUTPUT_REDIRECTION 2
# define TOKEN_OUTPUT_APPEND_EDIRECTION 3
# define TOKEN_INTPUT_REDIRECTION 4
# define TOKEN_INTPUT_HEREDOC_REDIRECTION 5
# define TOKEN_FILE 6
# define TOKEN_LIMITER 7
# define BUFFER_SIZE 1024

# define DOLLAR_NO 0
# define DOLLAR_MACRO 1

extern volatile sig_atomic_t	g_glob;

typedef struct s_manage_pipe
{
	int		i;
	int		j;
	int		k;
	int		v;
	int		size;
	int		end;
	int		nb_cmd;
	int		*size_cmd;
	char	**pipecmd;
}	t_manage_pipe;

typedef struct s_token
{
	int		type;
	int		len_value;
	int		is_dollar;
	int		nb_token;
	char	*value;
}	t_token;

typedef struct s_pipe
{
	t_token	*scmd;
	char	*cmd;
	int		len_cmd;
	int		nb_token;
	int		first;
}	t_pipe;

typedef struct s_envi
{
	char			*str;
	struct s_envi	*next;
}	t_envi;

typedef struct s_exec_single
{
	char	**allpaths;
	char	**cmdargs;
	char	*cmdstat;
	char	*cmddyn;
	int		redirout;
	int		redirin;
	int		inlast;
	int		nb_redirout;
	int		nb_redirin;
	int		is_here_doc;
}				t_exec_single;

typedef struct s_unset
{
	t_envi	*temp;
	t_envi	*prev;
	char	*vari;
}				t_unset;

typedef struct s_redup
{
	int		savein;
	int		saveout1;
	pid_t	c1;
	int		status;
}				t_redup;

typedef struct s_fullhd
{
	int		status;
	pid_t	child;
}				t_fullhd;

typedef struct s_dolret
{
	char	*ret;
	int		n;
	char	*itoa;
	char	*ptr;
}				t_dolret;

typedef struct s_fill
{
	int		j;
	int		n;
}				t_fill;

typedef struct s_ext
{
	t_envi	*temp;
	char	**av;
}				t_ext;

typedef struct s_nested
{
	char	**exp;
	char	**split;
	int		i;
	int		j;
	int		k;
}				t_nested;

typedef struct s_cmdtab
{
	int		i;
	int		vu;
	int		size;
}				t_cmdtab;

typedef struct s_hdc
{
	int	i;
	int	j;
	int	ret;
}				t_hdc;

typedef struct s_macro
{
	t_envi	*copy;
	char	*ret;
	char	*macro;
	int		i;
}				t_macro;

typedef struct s_exec_multi
{
	char	**allpaths;
	char	**cmdargs;
	char	*cmdstat;
	char	*cmddyn;
	int		redirin_fd;
	int		redirtrunc_fd;
	int		redirappend_fd;
	int		nb_redirout;
	int		nb_redirin;
	int		redirin;
	int		redirout;
	int		is_here_doc;
	pid_t	*c_pid;
	int		**pipe_fd;
}				t_exec_multi;

typedef struct s_shell
{
	int				nb_cell;
	int				exit_switch;
	int				error_ret;
	int				exit_ret;
	int				std_in;
	int				std_out;
	int				std_error;
	t_manage_pipe	mpipe;
	t_envi			*our_env;
	t_envi			*exports;
	t_pipe			*token;
}		t_shell;

void	forced_prompt(int sig);
void	forced_continue(int sig);
char	*check_line(char **line);
int		control(t_shell *data);
void	init_treat_redir_heredoc(t_shell *d, t_hdc *nup, int n);
void	free_struct(t_manage_pipe utils, t_pipe **prompt);
void	free_token(t_manage_pipe utils, t_pipe **prompt);
int		is_redirection(char c);
int		set_struct(char **line, t_manage_pipe utils, t_pipe **prompt);
void	*more_help_cmd_struct(int *nb_cmd, int *len_cmd, t_pipe **prompt);
void	*help_cmd_struct(int nb_cmd, int len_cmd, t_pipe **prompt);
void	*cmd_struct(t_manage_pipe utils, t_pipe **prompt);
void	*first_help_len_token(int *i, int *j, int *k, t_pipe **prompt);
void	*last_help_len_token(int *i, int *j, int *k, t_pipe **prompt);
void	*found_len_token(t_manage_pipe utils, t_pipe **prompt);
void	*malloc_set_token(t_manage_pipe utils, t_pipe **prompt);
void	*first_help_set_token(t_manage_pipe *data, int *v, t_pipe **prompt);
void	*last_help_set_token(t_manage_pipe *data, int *v, t_pipe **prompt);
void	*last_more_help_set_token(t_manage_pipe *data, int *v, t_pipe **prompt);
void	*set_token(t_manage_pipe utils, t_pipe **prompt);
void	*make_tab_cmd(t_manage_pipe *mpipe, char *line);
void	*set_manage(t_manage_pipe *mpipe, char *line);
int		len_cmd_pipe(t_manage_pipe *mpipe, char *line);
void	help_size(int *i, char *line);
int		size_cmd_tab(char *line);
char	*set_path(char **infos);
void	*determine_type(t_pipe *prompt, int i);
void	*all_pipe_cmd(t_manage_pipe *mpipe, char *line);
void	clean_manage(t_manage_pipe *mpipe, t_pipe **prompt);
void	*help_len_cmd(int *r, t_manage_pipe *mpipe, char *line);
void	*len_s_quote(int *r, t_manage_pipe *mpipe, char *line);
void	*len_d_quote(int *r, t_manage_pipe *mpipe, char *line);
int		len_redir(int *r, t_manage_pipe *mpipe, char *line);
void	*cpt_pipe(int *r, int *cmd, t_manage_pipe *mpipe, char *line);
t_envi	*init_our_env(char **env);
int		download_env_two(t_shell *shell_pack, char **env);
int		download_env_one(t_shell *shell_pack, char **env);
char	*get_next_line(int fd);
char	*gnl_strjoin(char *s1, char *s2);
int		has_space_in(t_shell *data, int cell_nb);
int		search_in_charray(char **super, char needle);
int		count_args(t_shell *data, int cell_nb);
char	**build_command(t_shell *data, int cell_nb);
char	**build_nested_command(t_shell *data, int cell_nb, char **args);
void	minishell_operator(t_shell *data);
void	execute_single_cmd(t_shell *data);
int		is_pathed(char *str);
void	init_box(t_dolret *box);
void	init_redir_dup_single(t_redup *red);
void	cmd_not_found(t_exec_single *data, char *av, char **env, t_shell *pack);
void	cannot_execute(t_exec_single *data, char *cmd, char **env, t_shell *p);
char	**charize_env(t_envi *env);
char	**get_allpaths(t_shell *data);
int		init_single_exe(t_shell *data, t_exec_single *exec_pack);
void	wrap_execve(t_exec_single *data, t_shell *shpack, char **env);
void	ft_execve_one(t_shell *shpack, char **env, t_exec_single *data);
void	ft_free_chr(char **super);
void	free_exec_pack(t_exec_single *pack);
void	ft_exec_built_in(t_shell *data, char **cmd);
int		ft_is_built_in(char *cmd);
int		my_env(t_envi *our_env, char **cmd);
int		my_pwd(char **args);
int		my_echo(char **cmd);
int		my_cd(char **cmd, t_envi *our_env);
void	my_exprint(t_envi *env);
int		my_export(char **cmd, t_envi *env, t_envi *exports);
void	set_newpwd(char *path, t_envi *our_env);
int		error_cd(char **cmd);
int		my_exit(char **cmd, t_shell *data);
char	*quit_dollar_deluxe(char *str, char *ret, char **split);
char	*dollar_swap(t_shell *shpack, char *str);
void	pipex(t_shell *data);
void	last_parent(t_shell *d, t_exec_multi *p, int n);
void	wrap_execve_multi(t_exec_multi *d, char **ag, char **env, t_shell *sh);
void	wait_all(t_shell *data, t_exec_multi *pack);
void	malloc_childs(t_shell *data, t_exec_multi *pack);
void	malloc_pipes(t_shell *data, t_exec_multi *pack);
int		mini_parse_multi(t_shell *data, t_exec_multi *exec_pack, int nb);
int		wrong_redir_multi(t_exec_multi *exec_pack, t_shell *data, int nb);
void	ft_execve_multi(t_shell *shpack, char **env, t_exec_multi *data);
void	free_exec_pack_multi(t_shell *data, t_exec_multi *pack);
void	cannot_execute_pipex(t_exec_multi *d, char *c, t_shell *sh, char **env);
void	cmd_not_found_pipex(t_exec_multi *d, char *c, t_shell *sh, char **env);
int		my_unset(char **cmd, t_shell *pack);
void	sig_exit(t_shell *data, int status, pid_t c1, char *cmd);
int		has_redir(t_shell *data, int cell_nb);
int		count_redir_in_simple(t_shell *data, t_exec_single *pack, int cell_nb);
int		count_redir_out_simple(t_shell *data, t_exec_single *pack, int cell_nb);
int		count_redir_heredoc_simple(t_shell *data, t_exec_single *pack);
int		treat_redir_heredoc(t_shell *d, t_exec_single *p);
int		treat_redir_in(t_shell *data, t_exec_single *pack, int n);
int		treat_redir_out(t_shell *d, t_exec_single *pack, int n);
int		here_doc_single(t_exec_single *data, char *lim, t_shell *pack);
void	redir_dup_single(t_shell *data, t_exec_single *pack);
void	redir_dup_multi(t_shell *data, t_exec_multi *pack, int cell_nb);
void	redir_dup_single_builtin(t_shell *data, t_exec_single *pack);
int		treat_redir_in_multi(t_shell *data, t_exec_multi *pack, int cell_nb);
int		treat_redir_out_multi(t_shell *d, t_exec_multi *p, int n);
int		count_redir_in_multi(t_shell *data, t_exec_multi *pack, int cell_nb);
int		count_redir_out_multi(t_shell *data, t_exec_multi *pack, int cell_nb);
void	child_doc(char *limiter, int *fd, t_shell *pack);
void	fake_here_doc(t_exec_single *data, char *lim);
int		get_last_redirin(t_shell *data, t_exec_single *pack);
void	fake_redoc(t_shell *data, t_exec_single *pack, int weight);
void	*ft_memdel(void *ptr);
char	*ft_strjoinmodtwo(char *s1, char *s2);
int		is_valid_identifier(char *cmd);
int		is_in_such_list(t_envi *list, char *str);
void	add_node_to_env(t_envi *list, char *str);
void	add_node_to_exp(t_envi *list, char *str);
int		is_valid_identifier_exp(char *cmd);
int		is_in_exp_list(t_envi *list, char *str);
char	**no_assign_export(char *str);
void	mid_child(t_shell *data, t_exec_multi *pack, int n);
int		ft_nt_att(t_envi *env, char *av);
void	fake_child_doc(char *limiter);
void	fake_redoc_m(t_shell *data, t_exec_multi *pack, int weight, int n);
void	fake_here_doc_m(t_exec_multi *data, char *lim);
int		here_doc_single_m(t_exec_multi *data, char *lim, int nb, t_shell *pack);
int		get_last_redirin_m(t_shell *data, t_exec_multi *pack, int cell_nb);
int		treat_redir_heredoc_m(t_shell *d, t_exec_multi *p, int nb);
int		count_redir_heredoc_multi(t_shell *data, t_exec_multi *pack, int n);
char	*ft_hd_dollar_check(char *str, t_shell *pack);
int		ft_syntax_error(void);
void	ft_free_env(t_envi *head);
int		dollar_count(char *str);
char	*dollar_deluxe(t_shell *shpack, char *str);
char	*ft_strjoinmod(char *s1, char *s2);
void	free_exec_pack(t_exec_single *pack);
void	clean_redir_single(t_exec_single *p, int in, int out1);
void	ft_init_cmdtab(t_cmdtab *data);
void	ft_init_cmdpipe(t_manage_pipe *mpipe);
void	ft_increment_cmdtab(t_cmdtab *data);
void	ft_initsetman(t_manage_pipe *mpipe, char *line);
char	*ft_exit_set_manage(t_manage_pipe *mpipe);
int		ft_is_dollar_cmd(t_shell *data, int cell_nb);
void	ft_incr(t_cmdtab *d);
void	legi_incr(int *k, int *v);
void	legi_incr2(int *v, int *j);
void	check_dolls(t_pipe **prompt, t_manage_pipe *data);
void	help_built_struct(int *len_cmd, int *first);
void	help_help(int *i, int *j, int *k, t_pipe **prompt);
int		wrong_redir(t_exec_single *exec_pack, t_shell *data);
int		infile_not_real_m(t_exec_multi *pack, int n, t_shell *data, int i);
int		infile_not_allowed_m(t_exec_multi *pack, int n, t_shell *data, int i);
int		outfile_not_allowed_m(t_exec_multi *pack, int n, t_shell *data, int i);
void	init_sig(void);
void	create_minimum_data(t_shell *data, char **env);
int		no_command_found(t_shell *data, int cell_nb);
void	sig_zigma(int sig);
int		stop_minishell(t_shell *shell_pack);
void	init_treat_redir_in_multi(t_shell *d, t_hdc *nup, int n);
void	init_treat_redir_out_multi(t_shell *d, t_hdc *nup, int n);
int		ft_only_redout(t_exec_single *pack, int *saveout1);
int		ft_only_redin(t_exec_single *pack);
int		ft_redirin_and_heredoc(t_shell *data, t_exec_single *pack);
int		ft_only_redout_m(t_exec_multi *pack);
int		ft_redirin_and_heredoc_m(t_shell *data, t_exec_multi *pack, int n);
int		ft_only_redin_m(t_exec_multi *pack);
void	clean_redir_multi(t_exec_multi *p, int in, int out1);
void	init_redir_dup_single(t_redup *red);
void	maxi_free(t_shell *data);
void	spec_free(t_shell *data, t_exec_single *pack);
void	spec_free_m(t_shell *data, t_exec_multi *pack);
int		has_only_monopoly_dollars(t_shell *data, int num);

#endif
