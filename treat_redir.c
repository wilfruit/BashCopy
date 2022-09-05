/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:30:36 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/05 13:41:50 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	clean_redir_single(t_exec_single *p, int in, int out1)
{
	if (p->nb_redirin || p->is_here_doc)
		dup2(in, 0);
	if (p->nb_redirout)
		dup2(out1, 1);
}

int	ft_redirin_and_heredoc(t_shell *data, t_exec_single *pack)
{
	int	fd;

	fd = dup(0);
	if (get_last_redirin(data, pack) == TOKEN_INTPUT_REDIRECTION)
	{
		fake_redoc(data, pack, 0);
		close(0);
		dup2(pack->redirin, 0);
	}
	if (get_last_redirin(data, pack) == TOKEN_INTPUT_HEREDOC_REDIRECTION)
	{
		fake_redoc(data, pack, 1);
		treat_redir_heredoc(data, pack);
	}
	return (fd);
}

int	ft_only_redin(t_exec_single *pack)
{
	int	fd;

	fd = dup(0);
	close(0);
	dup2(pack->redirin, 0);
	return (fd);
}

int	ft_only_redout(t_exec_single *pack)
{
	int	fd;

	fd = dup(1);
	close(1);
	dup2(pack->redirout, 1);
	return (fd);
}

void	redir_dup_single(t_shell *data, t_exec_single *pack)
{
	int		savein;
	int		saveout1;

	savein = 0;
	saveout1 = 0;
	if (pack->is_here_doc > 0 && pack->nb_redirin > 0)
		savein = ft_redirin_and_heredoc(data, pack);
	if (pack->is_here_doc > 0 && !(pack->nb_redirin > 0))
	{
		savein = dup(0);
		fake_redoc(data, pack, 1);
		treat_redir_heredoc(data, pack);
	}
	if (pack->nb_redirin > 0 && !(pack->is_here_doc > 0))
		savein = ft_only_redin(pack);
	if (pack->nb_redirout > 0)
		saveout1 = ft_only_redout(pack);
	if (ft_is_built_in(pack->cmdargs[0]) == 1)
		ft_exec_built_in(data, pack->cmdargs);
	else
		ft_execve_one(data, charize_env(data->our_env), pack);
	clean_redir_single(pack, savein, saveout1);
}