/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redir_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:16:17 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/19 16:37:34 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	clean_redir_multi(t_exec_multi *p, int in, int out1)
{
	if (p->redirin || p->is_here_doc)
		dup2(in, 0);
	if (p->redirout)
		dup2(out1, 1);
}

int	ft_redirin_and_heredoc_m(t_shell *data, t_exec_multi *pack, int n)
{
	if (get_last_redirin_m(data, pack, n) == TOKEN_INTPUT_REDIRECTION)
	{
		fake_redoc_m(data, pack, 0, n);
		close(0);
		dup2(pack->redirin, 0);
	}
	if (get_last_redirin_m(data, pack, n) == 5)
	{
		fake_redoc_m(data, pack, 1, n);
		if (treat_redir_heredoc_m(data, pack, n) == 1)
			return (1);
	}
	return (0);
}

int	ft_only_redin_m(t_exec_multi *pack)
{
	int	fd;

	fd = dup(0);
	close(0);
	dup2(pack->redirin, 0);
	return (fd);
}

int	ft_only_redout_m(t_exec_multi *pack)
{
	int	fd;

	fd = dup(1);
	close(1);
	dup2(pack->redirout, 1);
	return (fd);
}
