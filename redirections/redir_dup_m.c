/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_dup_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:37:06 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/19 16:37:20 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	init_redir_dup_single(t_redup *red)
{
	red->savein = 0;
	red->saveout1 = 0;
}

void	exec_dup_multi(t_shell *data, t_exec_multi *pack)
{
	if (ft_is_built_in(pack->cmdargs[0]) == 1)
	{
		ft_free_chr(pack->allpaths);
		ft_exec_built_in(data, pack->cmdargs);
	}
	else
		ft_execve_multi(data, charize_env(data->our_env), pack);
}

void	dup_case_no_cmd_m(t_shell *data, t_redup *red, t_exec_multi *pack)
{
	if (g_glob == 30)
		data->error_ret = 1;
	maxi_free(data);
	clean_redir_multi(pack, red->savein, red->saveout1);
	exit (data->error_ret);
}

void	dup_case_only_hd_m(t_shell *d, t_redup *red, t_exec_multi *p, int n)
{
	red->savein = dup(0);
	fake_redoc_m(d, p, 1, n);
	if (treat_redir_heredoc_m(d, p, n) == 1)
	{
		d->error_ret = 1;
		if (!no_command_found(d, n))
			spec_free_m(d, p);
		clean_redir_multi(p, red->savein, red->saveout1);
		maxi_free(d);
		exit(d->error_ret);
	}
}

void	redir_dup_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
	t_redup	red;

	init_redir_dup_single(&red);
	if (pack->is_here_doc > 0 && pack->nb_redirin > 0)
	{
		red.savein = dup(0);
		if (ft_redirin_and_heredoc_m(data, pack, cell_nb) == 1)
			exit(data->error_ret);
	}
	if (pack->nb_redirin > 0 && !(pack->is_here_doc > 0))
		red.savein = ft_only_redin_m(pack);
	if (pack->nb_redirout > 0)
		red.saveout1 = ft_only_redout_m(pack);
	if (pack->is_here_doc > 0 && !(pack->nb_redirin > 0))
		dup_case_only_hd_m(data, &red, pack, cell_nb);
	if (no_command_found(data, cell_nb) == 1)
		dup_case_no_cmd_m(data, &red, pack);
	if (data->error_ret != 2)
		exec_dup_multi(data, pack);
	clean_redir_multi(pack, red.savein, red.saveout1);
}
