/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:55:43 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/05 14:08:50 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	mid_child(t_shell *data, t_exec_multi *pack, int n)
{
	mini_parse_multi(data, pack, n);
	close(pack->pipe_fd[n][0]);
	if (!pack->nb_redirin && !pack->is_here_doc)
	{
		dup2(pack->pipe_fd[n - 1][0], STDIN_FILENO);
		close(pack->pipe_fd[n - 1][0]);
	}
	if (get_last_redirin_m(data, pack, n) != 5)
	{
		dup2(pack->pipe_fd[n][1], STDOUT_FILENO);
		close(pack->pipe_fd[n][1]);
	}
	if (pack->nb_redirin || pack->nb_redirout || pack->is_here_doc)
		redir_dup_multi(data, pack, n);
	else
		ft_execve_multi(data, charize_env(data->our_env), pack);
}

int	my_env(t_envi *our_env, char **cmd)
{
	t_envi	*copy;

	if (cmd[0] && cmd[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	copy = our_env;
	while (copy)
	{
		ft_putendl_fd(copy->str, 1);
		copy = copy->next;
	}
	return (0);
}
