/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_multi_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:33:07 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/18 20:20:08 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	hd_m_parent(int status, pid_t child, t_shell *pack)
{
	g_glob = 30;
	sig_exit(pack, status, child, "messge");
	pack->error_ret = 1;
	return (1);
}

int	here_doc_single_m(t_exec_multi *data, char *lim, int nb, t_shell *pack)
{
	pid_t	child;
	int		fd[2];
	int		status;

	pipe(fd);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	child = fork();
	if (child == 0)
	{
		signal(SIGINT, sig_zigma);
		if (!no_command_found(pack, nb))
			spec_free_m(pack, data);
		child_doc(ft_strdup(lim), fd, pack);
		maxi_free(pack);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		if (nb != pack->nb_cell - 1)
			dup2(data->pipe_fd[nb][1], STDOUT_FILENO);
		dup2(fd[0], 0);
		waitpid(child, &status, 0);
		if (status == 33280)
			return (hd_m_parent(status, child, pack));
		return (0);
	}
}

void	fake_redoc_m(t_shell *data, t_exec_multi *pack, int weight, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->token[n].scmd[i].type != 5 \
	&& i < data->token[n].nb_token)
		i++;
	while (j < pack->is_here_doc - weight)
	{
		if (data->token[n].scmd[i].type == 5 \
		&& (i + 1) < data->token[n].nb_token && \
		data->token[n].scmd[i + 1].type == TOKEN_LIMITER)
			fake_here_doc_m(pack, ft_strdup(data->token[n].scmd[i + 1].value));
		else if (data->token[n].scmd[i].type == 5 && \
		!((i + 1) < data->token[n].nb_token))
			data->error_ret = ft_syntax_error();
		i += 2;
		j++;
	}
}

int	get_last_redirin_m(t_shell *data, t_exec_multi *pack, int cell_nb)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (i < data->token[cell_nb].nb_token - 1)
	{
		if (data->token[cell_nb].scmd[i].type == 5)
			ret = TOKEN_INTPUT_HEREDOC_REDIRECTION;
		if (data->token[cell_nb].scmd[i].type == TOKEN_INTPUT_REDIRECTION)
			ret = TOKEN_INTPUT_REDIRECTION;
		i++;
	}
	return (ret);
}

int	treat_redir_heredoc_m(t_shell *d, t_exec_multi *p, int nb)
{
	t_hdc	nup;

	init_treat_redir_heredoc(d, &nup, nb);
	while (nup.j < p->is_here_doc)
	{
		if (d->token[nb].scmd[nup.i].type == 5 \
		&& (nup.i + 1) < d->token[nb].nb_token && \
		d->token[nb].scmd[nup.i + 1].type == 7 && nup.j == p->is_here_doc - 1)
			nup.ret = here_doc_single_m(p, \
		ft_strdup(d->token[nb].scmd[nup.i + 1].value), nb, d);
		else if (d->token[nb].scmd[nup.i].type == 5 \
		&& !((nup.i + 1) < d->token[nb].nb_token))
			d->error_ret = ft_syntax_error();
		if (nup.ret == 1)
			return (1);
		nup.i++;
		while (nup.i < d->token[nb].nb_token \
		&& d->token[nb].scmd[nup.i].type != 5)
			nup.i++;
		nup.j++;
	}
	return (0);
}
