/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_dup_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:21:44 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/20 15:31:45 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	exec_dup(t_redup *red, t_shell *data, t_exec_single *pack)
{
	int	status;

	red->c1 = fork();
	if (red->c1 == 0 && ft_is_built_in(pack->cmdargs[0]) == 1)
	{
		ft_exec_built_in(data, pack->cmdargs);
		maxi_free(data);
		spec_free(data, pack);
		exit(data->error_ret);
	}
	else if (red->c1 == 0 && ft_is_built_in(pack->cmdargs[0]) != 1)
		ft_execve_one(data, charize_env(data->our_env), pack);
	waitpid(red->c1, &status, 0);
	if (WIFEXITED(status))
		data->error_ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		sig_exit(data, status, red->c1, pack->cmdargs[0]);
	spec_free(data, pack);
}

void	dup_case_no_cmd(t_shell *data, t_redup *red, t_exec_single *pack)
{
	if (g_glob == 30)
		data->error_ret = 1;
	return (clean_redir_single(pack, red->savein, red->saveout1));
}

void	dup_case_hd_error(t_shell *data, t_redup *red, t_exec_single *pack)
{
	data->error_ret = 1;
	return (clean_redir_single(pack, red->savein, red->saveout1));
}

void	init_redir_dup_single(t_redup *red)
{
	red->savein = 0;
	red->saveout1 = 0;
}

void	redir_dup_single(t_shell *data, t_exec_single *pack)
{
	t_redup	red;

	init_redir_dup_single(&red);
	if (pack->is_here_doc > 0 && pack->nb_redirin > 0)
	{
		red.savein = dup(0);
		if (ft_redirin_and_heredoc(data, pack) == 1)
			return (dup_case_hd_error(data, &red, pack));
	}
	if (pack->is_here_doc > 0 && !(pack->nb_redirin > 0))
	{
		red.savein = dup(0);
		fake_redoc(data, pack, 1);
		if (treat_redir_heredoc(data, pack) == 1)
			return (dup_case_hd_error(data, &red, pack));
	}
	if (pack->nb_redirin > 0 && !(pack->is_here_doc > 0))
		red.savein = ft_only_redin(pack);
	if (pack->nb_redirout > 0)
		ft_only_redout(pack, &red.saveout1);
	if (no_command_found(data, 0) == 1)
		return (dup_case_no_cmd(data, &red, pack));
	if (data->error_ret != 2)
		exec_dup(&red, data, pack);
	if (data->error_ret == 2 && !no_command_found(data, 0))
		spec_free(data, pack);
	clean_redir_single(pack, red.savein, red.saveout1);
}
