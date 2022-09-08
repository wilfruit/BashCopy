/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <avaures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:13:31 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/08 17:56:49 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	get_last_redirin(t_shell *data, t_exec_single *pack)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (i < data->token[0].nb_token - 1)
	{
		if (data->token[0].scmd[i].type == TOKEN_INTPUT_HEREDOC_REDIRECTION)
			ret = TOKEN_INTPUT_HEREDOC_REDIRECTION;
		if (data->token[0].scmd[i].type == TOKEN_INTPUT_REDIRECTION)
			ret = TOKEN_INTPUT_REDIRECTION;
		i++;
	}
	return (ret);
}

int	count_redir_heredoc_simple(t_shell *data, t_exec_single *pack)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < data->token[0].nb_token - 1)
	{
		if (data->token[0].scmd[i].type == TOKEN_INTPUT_HEREDOC_REDIRECTION)
			count++;
		i++;
	}
	return (count);
}

int	count_redir_out_simple(t_shell *data, t_exec_single *pack, int cell_nb)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < data->token[cell_nb].nb_token - 1)
	{
		if (data->token[cell_nb].scmd[i].type == TOKEN_OUTPUT_REDIRECTION || \
		data->token[cell_nb].scmd[i].type == TOKEN_OUTPUT_APPEND_EDIRECTION)
			count++;
		i++;
	}
	return (count);
}

int	count_redir_in_simple(t_shell *data, t_exec_single *pack, int cell_nb)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < data->token[cell_nb].nb_token - 1)
	{
		if (data->token[cell_nb].scmd[i].type == TOKEN_INTPUT_REDIRECTION)
			count++;
		i++;
	}
	return (count);
}

int	treat_redir_heredoc(t_shell *d, t_exec_single *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (d->token[0].scmd[i].type != 5 \
	&& i < d->token[0].nb_token)
		i++;
	while (j < p->is_here_doc)
	{
		if (d->token[0].scmd[i].type == 5 \
		&& (i + 1) < d->token[0].nb_token && \
		d->token[0].scmd[i + 1].type == 7 && \
		j == p->is_here_doc - 1)
			here_doc_single(p, ft_strdup(d->token[0].scmd[i + 1].value), d);
		else if (d->token[0].scmd[i].type == 5 \
		&& !((i + 1) < d->token[0].nb_token))
			d->error_ret = ft_syntax_error();
		i++;
		while (i < d->token[0].nb_token && \
		d->token[0].scmd[i].type != 5)
			i++;
		j++;
	}
}
