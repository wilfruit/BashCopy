/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:17:54 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/05 16:20:50 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	treat_redir_out(t_shell *data, t_exec_single *pack, int cell_nb)
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
		if (data->token[cell_nb].scmd[i].type == 4)
			pack->redirout = open(data->token[cell_nb].scmd[i + 1].value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->token[cell_nb].scmd[i].type == 3)
			pack->redirout = open(data->token[cell_nb].scmd[i + 1].value, O_CREAT | O_RDWR | O_APPEND, 0644);
			i += 2;
		j++;
	}
}

void	treat_redir_in(t_shell *data, t_exec_single *pack, int cell_nb)
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
		if (data->token[cell_nb].scmd[i].type == 4)
			pack->redirin = open(data->token[cell_nb].scmd[i + 1].value, O_RDONLY);
		i += 2;
		j++;
	}
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
