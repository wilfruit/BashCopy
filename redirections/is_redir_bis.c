/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:17:54 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/19 02:19:13 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	outfile_not_a(t_exec_single *pack, int n, t_shell *data, int i)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(data->token[n].scmd[i + 1].value, 2);
	ft_putendl_fd(" : Permission denied", 2);
	data->error_ret = 1;
	return (1);
}

int	treat_redir_out(t_shell *d, t_exec_single *pack, int n)
{
	t_hdc	nup;

	pack->redirout = 1;
	init_treat_redir_out_multi(d, &nup, n);
	while (nup.j < pack->nb_redirout)
	{
		if (d->token[n].scmd[nup.i].type == 2 \
		&& (nup.i + 1) < d->token[n].nb_token)
			pack->redirout = \
open(d->token[n].scmd[nup.i + 1].value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (d->token[n].scmd[nup.i].type == 3 \
		&& (nup.i + 1) < d->token[n].nb_token)
			pack->redirout = \
open(d->token[n].scmd[nup.i + 1].value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (pack->redirout == -1)
			return (outfile_not_a(pack, n, d, nup.i));
		if ((d->token[n].scmd[nup.i].type == 2 \
		|| d->token[n].scmd[nup.i].type == 3) \
		&& !((nup.i + 1) < d->token[n].nb_token))
			d->error_ret = ft_syntax_error();
		nup.i += 2;
		nup.j++;
	}
	return (0);
}

static int	infile_not_allowed(t_exec_single *p, int n, t_shell *d, int i)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(d->token[n].scmd[i + 1].value, 2);
	ft_putendl_fd(" Permission denied", 2);
	d->error_ret = 1;
	return (1);
}

static int	infile_not_real(t_exec_single *p, int n, t_shell *d, int i)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(d->token[n].scmd[i + 1].value, 2);
	ft_putendl_fd(" No such file or directory", 2);
	d->error_ret = 1;
	return (1);
}

int	treat_redir_in(t_shell *data, t_exec_single *pack, int n)
{
	t_hdc	nup;

	pack->redirin = 0;
	init_treat_redir_in_multi(data, &nup, n);
	while (nup.j < pack->nb_redirin)
	{
		if (data->token[n].scmd[nup.i].type == 4 \
		&& ((nup.i + 1) < data->token[n].nb_token))
		{
			if (access(data->token[n].scmd[nup.i + 1].value, R_OK) != 0 && \
			access(data->token[n].scmd[nup.i +1].value, F_OK) == 0)
				return (infile_not_allowed(pack, n, data, nup.i));
			if (access(data->token[n].scmd[nup.i + 1].value, F_OK) != 0)
				return (infile_not_real(pack, n, data, nup.i));
			pack->redirin = \
open(data->token[n].scmd[nup.i + 1].value, O_RDONLY);
		}
		if (data->token[n].scmd[nup.i].type == 4 \
		&& !((nup.i + 1) < data->token[n].nb_token))
			data->error_ret = ft_syntax_error();
		nup.i += 2;
		nup.j++;
	}
	return (0);
}
