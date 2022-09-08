/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_more_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:17:47 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/08 16:07:59 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	wrap_execve_multi(t_exec_multi *data, char **args, char **env, t_shell *shell)
{
	execve(data->cmddyn, args, env);
	cannot_execute_pipex(data, data->cmddyn, shell);
}

static void	ft_free_pipes(t_shell *data, t_exec_multi *pack)
{
	int	i;

	i = 0;
	while (i < data->nb_cell - 1)
	{
		free(pack->pipe_fd[i]);
		i++;
	}
	free(pack->pipe_fd);
}

void	free_exec_pack_multi(t_shell *data, t_exec_multi *pack)
{
	ft_free_chr(pack->allpaths);
	ft_free_pipes(data, pack);
	free(pack->c_pid);
}

void	cannot_execute_pipex(t_exec_multi *data, char *cmd, t_shell *shell)
{
	ft_putstr_fd("minishell: permission denied: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	free_exec_pack_multi(shell, data);
	exit(126);
}

void	cmd_not_found_pipex(t_exec_multi *data, char *argv, t_shell *shell)
{	
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_exec_pack_multi(shell, data);
	exit(127);
}
