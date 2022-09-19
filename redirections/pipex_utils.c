/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:50:27 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/18 20:25:50 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	malloc_childs(t_shell *data, t_exec_multi *pack)
{
	pack->c_pid = (pid_t *)malloc(sizeof(pid_t) * data->nb_cell);
	if (!pack->c_pid)
		perror("Malloc : ");
}

void	malloc_pipes(t_shell *data, t_exec_multi *pack)
{
	int	i;

	i = 0;
	pack->pipe_fd = (int **)malloc(sizeof(int *) * (data->nb_cell - 1));
	if (!pack->pipe_fd)
		perror("Malloc : ");
	while (i < data->nb_cell - 1)
	{
		pack->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!pack->pipe_fd[i])
			perror("Malloc : ");
		i++;
	}	
}

int	mini_parse_multi(t_shell *data, t_exec_multi *exec_pack, int nb)
{
	exec_pack->nb_redirin = count_redir_in_multi(data, exec_pack, nb);
	exec_pack->nb_redirout = count_redir_out_multi(data, exec_pack, nb);
	exec_pack->is_here_doc = count_redir_heredoc_multi(data, exec_pack, nb);
	if (wrong_redir_multi(exec_pack, data, nb))
		return (1);
	if (data->our_env->next == NULL)
	{
		exec_pack->allpaths = (char **)malloc(sizeof(char *));
		exec_pack->allpaths[0] = NULL;
	}
	else
		exec_pack->allpaths = get_allpaths(data);
/* 	if (exec_pack->cmdargs && exec_pack->cmdargs[0])
		free (exec_pack->cmdargs); */
	if (!no_command_found(data, nb))
		exec_pack->cmdargs = build_command(data, nb);
	if (!no_command_found(data, nb) && ft_is_built_in(exec_pack->cmdargs[0]) != 1)
	{
		exec_pack->cmdstat = ft_strdup(exec_pack->cmdargs[0]);
		exec_pack->cmdstat = ft_strjoin("/", exec_pack->cmdstat);
	}
	return (0);
}

void	ft_execve_multi(t_shell *shpack, char **env, t_exec_multi *data)
{
	int	i;

	i = -1;
	if (!shpack)
		return ;
	if (ft_is_built_in(data->cmdargs[0]) == 1)
		ft_exec_built_in(shpack, data->cmdargs);
	while (data->allpaths[++i])
	{
		if (is_pathed(data->cmdargs[0]) == -1)
			data->cmddyn = ft_strjoin(data->allpaths[i], data->cmdstat);
		else
			data->cmddyn = data->cmdargs[0];
		if ((is_pathed(data->cmdargs[0]) == 0 \
		&& access(data->cmddyn, F_OK) != 0) \
		|| ft_strncmp(data->cmddyn, "/", ft_strlen(data->cmddyn)) == 0 || \
		ft_strncmp(data->cmddyn, "./", ft_strlen(data->cmddyn)) == 0)
			cmd_not_found_pipex(data, data->cmdargs[0], shpack);
		if (access(data->cmddyn, F_OK) == 0 && access(data->cmddyn, X_OK) == 0)
			wrap_execve_multi(data, data->cmdargs, env, shpack);
		if (is_pathed(data->cmdargs[0]) == 0 && access(data->cmddyn, X_OK) != 0)
			cannot_execute_pipex(data, data->cmdargs[0], shpack);
		free(data->cmddyn);
	}
	cmd_not_found_pipex(data, data->cmdargs[0], shpack);
}
