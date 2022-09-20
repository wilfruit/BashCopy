/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir_multi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:04:18 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/19 02:19:07 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	count_redir_out_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < data->token[cell_nb].nb_token)
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
	while (i < data->token[cell_nb].nb_token)
	{
		if (data->token[cell_nb].scmd[i].type == 4)
			count++;
		i++;
	}
	return (count);
}

int	count_redir_heredoc_multi(t_shell *data, t_exec_multi *pack, int n)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < data->token[n].nb_token)
	{
		if (data->token[n].scmd[i].type == 5)
			count++;
		i++;
	}
	return (count);
}

int	treat_redir_out_multi(t_shell *d, t_exec_multi *p, int n)
{
	t_hdc	nup;

	init_treat_redir_out_multi(d, &nup, n);
	while (nup.j < p->nb_redirout)
	{
		if (d->token[n].scmd[nup.i].type == 2 \
		&& (nup.i + 1) < d->token[n].nb_token)
			p->redirout = \
open(d->token[n].scmd[nup.i + 1].value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (d->token[n].scmd[nup.i].type == 3 \
		&& (nup.i + 1) < d->token[n].nb_token)
			p->redirout = \
open(d->token[n].scmd[nup.i + 1].value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (p->redirout == -1)
			return (outfile_not_allowed_m(p, n, d, nup.i));
		if ((d->token[n].scmd[nup.i].type == 2 \
		|| d->token[n].scmd[nup.i].type == 3) \
		&& !((nup.i + 1) < d->token[n].nb_token))
			d->error_ret = ft_syntax_error();
		nup.i += 2;
		nup.j++;
	}
	return (0);
}

int	treat_redir_in_multi(t_shell *data, t_exec_multi *pack, int cell_nb)
{
	t_hdc	nup;

	init_treat_redir_in_multi(data, &nup, cell_nb);
	while (nup.j < pack->nb_redirin)
	{
		if (data->token[cell_nb].scmd[nup.i].type == 4 \
		&& ((nup.i + 1) < data->token[cell_nb].nb_token))
		{
			if (access(data->token[cell_nb].scmd[nup.i + 1].value, R_OK) != 0 \
			&& access(data->token[cell_nb].scmd[nup.i +1].value, F_OK) == 0)
				return (infile_not_allowed_m(pack, cell_nb, data, nup.i));
			if (access(data->token[cell_nb].scmd[nup.i + 1].value, F_OK) != 0)
				return (infile_not_real_m(pack, cell_nb, data, nup.i));
			pack->redirin = \
				open(data->token[cell_nb].scmd[nup.i + 1].value, O_RDONLY);
		}
		if (data->token[cell_nb].scmd[nup.i].type == 4 \
		&& !((nup.i + 1) < data->token[cell_nb].nb_token))
			data->error_ret = ft_syntax_error();
		nup.i += 2;
		nup.j++;
	}
	return (0);
}
