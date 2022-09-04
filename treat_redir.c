/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:30:36 by wgaspar           #+#    #+#             */
/*   Updated: 2022/08/31 16:40:29 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	clean_redir_single(t_exec_single *p, int in, int out1)
{
	if (p->nb_redirin || p->is_here_doc)
		dup2(in, 0);
	if (p->nb_redirout)
		dup2(out1, 1);
}

static void	clean_redir_multi(t_exec_multi *p, int in, int out1)
{
	if (p->redirin || p->is_here_doc)
		dup2(in, 0);
	if (p->redirout)
		dup2(out1, 1);
}

// copier le fonctionne;ent de celui du dessous fdp

void	redir_dup_single_builtin(t_shell *data, t_exec_single *pack)
{
	int		savein;
	int		saveout1;

	savein = 0;
	saveout1 = 0;
	if (pack->nb_redirin > 0)
	{
		savein = dup(0);
		close(0);
		dup2(pack->redirin, 0);
	}
	if (pack->nb_redirout > 0)
	{
		saveout1 = dup(1);
		close(1);
		dup2(pack->redirout, 1);
	}
	ft_exec_built_in(data, pack->cmdargs);
	clean_redir_single(pack, savein, saveout1);
}

void	redir_dup_single(t_shell *data, t_exec_single *pack)
{
	int		savein;
	int		saveout1;

	savein = 0;
	saveout1 = 0;
	if (pack->is_here_doc > 0 && pack->nb_redirin > 0)
	{
		savein = dup(0);
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
	}
	if (pack->is_here_doc > 0 && !(pack->nb_redirin > 0))
	{
		savein = dup(0);
		fake_redoc(data, pack, 1);
		treat_redir_heredoc(data, pack);
	}
	if (pack->nb_redirin > 0 && !(pack->is_here_doc > 0))
	{
		savein = dup(0);
		close(0);
		dup2(pack->redirin, 0);
	}
	if (pack->nb_redirout > 0)
	{
		saveout1 = dup(1);
		close(1);
		dup2(pack->redirout, 1);
	}
	if (ft_is_built_in(pack->cmdargs[0]) == 1)
		ft_exec_built_in(data, pack->cmdargs);
	else
		ft_execve_one(data, charize_env(data->our_env), pack);
	clean_redir_single(pack, savein, saveout1);
}

void	redir_dup_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
	int		savein;
	int		saveout1;

	savein = 0;
	saveout1 = 0;
	if (pack->is_here_doc > 0 && pack->nb_redirin > 0)
	{
		savein = dup(0);
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
	}
	if (pack->nb_redirin > 0 && !(pack->is_here_doc > 0))
	{
		savein = dup(0);
		close(0);
		dup2(pack->redirin, 0);
	}
	if (pack->nb_redirout > 0)
	{
		saveout1 = dup(1);
		close(1);
		dup2(pack->redirout, 1);
	}
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
