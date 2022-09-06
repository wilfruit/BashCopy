/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:54:46 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 16:55:13 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	**get_allpaths(t_shell *data)
{
	t_envi	*tmp;
	char	*path_in_env;
	char	**allpaths;

	tmp = data->our_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "PATH=", 5) == 0)
		{
			path_in_env = ft_strdup(tmp->str + 5);
			allpaths = ft_split(path_in_env, ':');
			free(path_in_env);
			return (allpaths);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	init_single_exe(t_shell *data, t_exec_single *exec_pack)
{
	exec_pack->cmdargs = build_command(data, 0);
	if (data->our_env->next == NULL \
	&& ft_is_built_in(exec_pack->cmdargs[0]) != 1)
	{
		exec_pack->allpaths = (char **)malloc(sizeof(char *));
		exec_pack->allpaths[0] = NULL;
	}
	else if (data->our_env->next && ft_is_built_in(exec_pack->cmdargs[0]) != 1)
		exec_pack->allpaths = get_allpaths(data);
	if (ft_is_built_in(exec_pack->cmdargs[0]) != 1)
	{
		exec_pack->cmdstat = exec_pack->cmdargs[0];
		exec_pack->cmdstat = ft_strjoin("/", exec_pack->cmdstat);
	}
	exec_pack->inlast = get_last_redirin(data, exec_pack);
	exec_pack->nb_redirin = count_redir_in_simple(data, exec_pack, 0);
	exec_pack->nb_redirout = count_redir_out_simple(data, exec_pack, 0);
	exec_pack->is_here_doc = count_redir_heredoc_simple(data, exec_pack);
	if (exec_pack->nb_redirout)
		treat_redir_out(data, exec_pack, 0);
	if (exec_pack->nb_redirin)
		treat_redir_in(data, exec_pack, 0);
}

static void	ft_normal_exe(t_exec_single *exec_pack, t_shell *data)
{
	pid_t	c1;
	int		status;

	c1 = fork();
	if (c1 < 0)
		perror("Fork : ");
	if (c1 == 0 && (exec_pack->nb_redirin \
	|| exec_pack->nb_redirout || exec_pack->is_here_doc))
		redir_dup_single(data, exec_pack);
	if (c1 == 0 && !exec_pack->nb_redirin \
	&& !exec_pack->nb_redirout && !exec_pack->is_here_doc)
		ft_execve_one(data, charize_env(data->our_env), exec_pack);
	waitpid(c1, &status, 0);
	if (exec_pack->cmdstat)
		free(exec_pack->cmdstat);
	ft_free_chr(exec_pack->allpaths);
	if (WIFEXITED(status))
		data->error_ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		sig_exit(data, status, c1, exec_pack->cmdargs[0]);
	ft_free_chr(exec_pack->cmdargs);
}

void	execute_single_cmd(t_shell *data)
{
	t_exec_single	exec_pack;

	init_single_exe(data, &exec_pack);
	if (ft_is_built_in(exec_pack.cmdargs[0]) == 1 && exec_pack.nb_redirin <= 0 \
	&& exec_pack.nb_redirout <= 0)
		ft_exec_built_in(data, exec_pack.cmdargs);
	else if (ft_is_built_in(exec_pack.cmdargs[0]) == 1 \
	&& (exec_pack.nb_redirin > 0 || \
	exec_pack.nb_redirout > 0))
		redir_dup_single(data, &exec_pack);
	else
		ft_normal_exe(&exec_pack, data);
}

void	minishell_operator(t_shell *data)
{
	if (data->nb_cell == 1)
		execute_single_cmd(data);
	if (data->nb_cell < 1)
		return ;
	if (data->nb_cell > 1)
	{
		pipex(data);
	}
	return ;
}
