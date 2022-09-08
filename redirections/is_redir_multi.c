/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir_multi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:04:18 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/08 13:41:59 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	count_redir_out_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < data->token[cell_nb].nb_token - 1)
	{
		if (data->token[cell_nb].scmd[i].type == 2 || \
		data->token[cell_nb].scmd[i].type == 3)
			count++;
		i++;
	}
	return (count);
}

int	count_redir_in_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < data->token[cell_nb].nb_token - 1)
	{
		if (data->token[cell_nb].scmd[i].type == 4)
			count++;
		i++;
	}
	return (count);
}

int	count_redir_heredoc_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < data->token[cell_nb].nb_token - 1)
	{
		if (data->token[cell_nb].scmd[i].type == 5)
			count++;
		i++;
	}
	return (count);
}

int	treat_redir_out_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((data->token[cell_nb].scmd[i].type != 2 \
	&& data->token[cell_nb].scmd[i].type != 3) \
	&& i < data->token[cell_nb].nb_token)
		i++;
	while (j < pack->nb_redirout)
	{
		if (access(data->token[cell_nb].scmd[i + 1].value, W_OK) != 0)
			return (outfile_not_allowed_m(pack, cell_nb, data, i));
		if (data->token[cell_nb].scmd[i].type == TOKEN_OUTPUT_REDIRECTION)
			pack->redirout = \
open(data->token[cell_nb].scmd[i + 1].value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->token[cell_nb].scmd[i].type == TOKEN_OUTPUT_APPEND_EDIRECTION)
			pack->redirout = \
open(data->token[cell_nb].scmd[i + 1].value, O_CREAT | O_RDWR | O_APPEND, 0644);
		i += 2;
		j++;
	}
}

int	treat_redir_in_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->token[cell_nb].scmd[i].type != 4 \
	&& i < data->token[cell_nb].nb_token)
		i++;
	while (j < pack->nb_redirin)
	{
		if (access(data->token[cell_nb].scmd[i + 1].value, R_OK) != 0 && \
			access(data->token[cell_nb].scmd[i +1].value, F_OK) == 0)
			return (infile_not_allowed_m(pack, cell_nb, data, i));
		if (access(data->token[cell_nb].scmd[i + 1].value, F_OK) != 0)
			return (infile_not_real_m(pack, cell_nb, data, i));		
		if (data->token[cell_nb].scmd[i].type == TOKEN_INTPUT_REDIRECTION)
			pack->redirin = \
open(data->token[cell_nb].scmd[i + 1].value, O_RDONLY);
		i += 2;
		j++;
	}
}
