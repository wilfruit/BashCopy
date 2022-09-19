/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_seven.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:26:29 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/19 14:27:22 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	help_help(int *i, int *j, int *k, t_pipe **prompt)
{
	(*prompt)[*i].scmd[*k].len_value += 1;
	*j += 1;
}

int	has_redir(t_shell *data, int cell_nb)
{
	int	i;

	i = 0;
	while (i < data->token[cell_nb].nb_token - 1)
	{
		if (data->token[cell_nb].scmd[i].type == TOKEN_OUTPUT_REDIRECTION || \
		data->token[cell_nb].scmd[i].type == TOKEN_INTPUT_REDIRECTION || \
		data->token[cell_nb].scmd[i].type == 5 || \
		data->token[cell_nb].scmd[i].type == TOKEN_OUTPUT_APPEND_EDIRECTION)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	wait_all(t_shell *data, t_exec_multi *pack)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nb_cell - 1)
	{
		waitpid(pack->c_pid[i], NULL, 0);
		i++;
	}
	waitpid(pack->c_pid[i], &status, 0);
	if (WIFEXITED(status))
		data->error_ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		sig_exit(data, status, pack->c_pid[i], "");
	else
		free_exec_pack_multi(data, pack);
}

int	wrong_redir(t_exec_single *exec_pack, t_shell *data)
{
	int	i;

	i = 0;
	if (exec_pack->nb_redirin)
		i = treat_redir_in(data, exec_pack, 0);
	if (i == 1)
		return (1);
	if (exec_pack->nb_redirout)
		i = treat_redir_out(data, exec_pack, 0);
	if (i == 1)
		return (1);
	return (0);
}

int	wrong_redir_multi(t_exec_multi *exec_pack, t_shell *data, int nb)
{
	int	i;

	i = 0;
	if (exec_pack->nb_redirin)
		i = treat_redir_in_multi(data, exec_pack, nb);
	if (i == 1)
		return (1);
	if (exec_pack->nb_redirout)
		i = treat_redir_out_multi(data, exec_pack, nb);
	if (i == 1)
		return (1);
	return (0);
}
