/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redir_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:16:17 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 17:16:18 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static void	clean_redir_multi(t_exec_multi *p, int in, int out1)
{
	if (p->redirin || p->is_here_doc)
		dup2(in, 0);
	if (p->redirout)
		dup2(out1, 1);
}

int	ft_redirin_and_heredoc_m(t_shell *data, t_exec_multi *pack, int cell_nb)
{
	int	fd;

	fd = dup(0);
	if (get_last_redirin_m(data, pack, cell_nb) == TOKEN_INTPUT_REDIRECTION)
	{
		fake_redoc_m(data, pack, 0, cell_nb);
		close(0);
		dup2(pack->redirin, 0);
	}
	if (get_last_redirin_m(data, pack, cell_nb) == 5)
	{
		fake_redoc_m(data, pack, 1, cell_nb);
		treat_redir_heredoc_m(data, pack, cell_nb);
	}
	return (fd);
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

void	redir_dup_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
	int		savein;
	int		saveout1;

	savein = 0;
	saveout1 = 0;
	if (pack->is_here_doc > 0 && pack->nb_redirin > 0)
		savein = ft_redirin_and_heredoc_m(data, pack, cell_nb);
	if (pack->nb_redirin > 0 && !(pack->is_here_doc > 0))
		savein = ft_only_redin_m(pack);
	if (pack->nb_redirout > 0)
		saveout1 = ft_only_redout_m(pack);
	if (pack->is_here_doc > 0 && !(pack->nb_redirin > 0))
	{
		savein = dup(0);
		fake_redoc_m(data, pack, 1, cell_nb);
		treat_redir_heredoc_m(data, pack, cell_nb);
	}
	if (ft_is_built_in(pack->cmdargs[0]) == 1)
		ft_exec_built_in(data, pack->cmdargs);
	else
		ft_execve_multi(data, charize_env(data->our_env), pack);
	clean_redir_multi(pack, savein, saveout1);
}
