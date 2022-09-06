/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_multi_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:33:07 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 01:50:29 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	here_doc_single_m(t_exec_multi *data, char *lim, int nb, t_shell *pack)
{
	pid_t	child;
	int		fd[2];

	pipe(fd);
	child = fork();
	if (child < 0)
		return ;
	if (child == 0)
		child_doc(lim, fd, pack);
	else
	{
		close(fd[1]);
		if (nb != pack->nb_cell)
			dup2(data->pipe_fd[nb][1], STDOUT_FILENO);
		dup2(fd[0], 0);
		waitpid(child, NULL, 0);
	}
}

void	fake_here_doc_m(t_exec_multi *data, char *lim)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return ;
	if (child == 0)
	{
		fake_child_doc(lim);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(child, NULL, 0);
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
		{
			data->error_ret = 258;
			ft_putstr_fd("minishell: syntax error ", 2);
			ft_putstr_fd("near unexpected token `newline'\n", 2);
		}
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

void	treat_redir_heredoc_m(t_shell *d, t_exec_multi *p, int nb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (d->token[nb].scmd[i].type != 5 && i < d->token[nb].nb_token)
		i++;
	while (j < p->is_here_doc)
	{
		if (d->token[nb].scmd[i].type == 5 \
		&& (i + 1) < d->token[nb].nb_token && \
		d->token[nb].scmd[i + 1].type == 7 && j == p->is_here_doc - 1)
			here_doc_single_m(p, \
		ft_strdup(d->token[nb].scmd[i + 1].value), nb, d);
		else if (d->token[nb].scmd[i].type == 5 \
		&& !((i + 1) < d->token[nb].nb_token))
			d->error_ret = ft_syntax_error();
		i++;
		while (i < d->token[nb].nb_token \
		&& d->token[nb].scmd[i].type != 5)
			i++;
		j++;
	}
}
