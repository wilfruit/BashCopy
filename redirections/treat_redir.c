/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:30:36 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/19 16:20:30 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	clean_redir_single(t_exec_single *p, int in, int out1)
{
	if (p->nb_redirin || p->is_here_doc)
		dup2(in, 0);
	if (p->nb_redirout)
		dup2(out1, 1);
}

int	ft_redirin_and_heredoc(t_shell *data, t_exec_single *pack)
{
	if (get_last_redirin(data, pack) == TOKEN_INTPUT_REDIRECTION)
	{
		fake_redoc(data, pack, 0);
		close(0);
		dup2(pack->redirin, 0);
	}
	if (get_last_redirin(data, pack) == TOKEN_INTPUT_HEREDOC_REDIRECTION)
	{
		fake_redoc(data, pack, 1);
		if (treat_redir_heredoc(data, pack) == 1)
			return (1);
	}
	return (0);
}

int	ft_only_redin(t_exec_single *pack)
{
	int	fd;

	fd = dup(0);
	close(0);
	dup2(pack->redirin, 0);
	return (fd);
}

int	ft_only_redout(t_exec_single *pack, int *saveout1)
{
	*saveout1 = dup(1);
	close(1);
	dup2(pack->redirout, 1);
	return (0);
}
