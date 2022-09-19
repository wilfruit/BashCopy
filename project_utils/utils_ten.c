/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ten.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:47:04 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/19 16:42:07 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	last_parent(t_shell *d, t_exec_multi *p, int n)
{
	close(p->pipe_fd[n - 1][0]);
	if (get_last_redirin_m(d, p, n) == 5)
		waitpid(p->c_pid[n], NULL, 0);
}

void	init_treat_redir_heredoc(t_shell *d, t_hdc *nup, int n)
{
	nup->ret = 0;
	nup->i = 0;
	nup->j = 0;
	while (d->token[n].scmd[nup->i].type != 5 \
	&& nup->i < d->token[n].nb_token)
		nup->i++;
}

void	init_treat_redir_in_multi(t_shell *d, t_hdc *nup, int n)
{
	nup->ret = 0;
	nup->i = 0;
	nup->j = 0;
	while (d->token[n].scmd[nup->i].type != 4 \
	&& nup->i < d->token[n].nb_token)
		nup->i++;
}

void	init_treat_redir_out_multi(t_shell *d, t_hdc *nup, int n)
{
	nup->ret = 0;
	nup->i = 0;
	nup->j = 0;
	while (d->token[n].scmd[nup->i].type != 2 \
	&& d->token[n].scmd[nup->i].type != 3 \
	&& nup->i < d->token[n].nb_token)
		nup->i++;
}

void	fake_here_doc_m(t_exec_multi *data, char *lim)
{
	pid_t	child;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	child = fork();
	if (child < 0)
		return ;
	if (child == 0)
	{
		signal(SIGINT, sig_zigma);
		fake_child_doc(lim);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(child, NULL, 0);
	}
}
