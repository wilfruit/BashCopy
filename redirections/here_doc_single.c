/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_single.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:08:17 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 01:50:23 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	child_doc(char *limiter, int *fd, t_shell *pack)
{
	char	*str;

	close(fd[0]);
	limiter = ft_strjoinmod(limiter, "\n");
	while (1)
	{
		str = readline("hd> ");
		if (ft_strncmp(limiter, str, ft_strlen(str)) != 0)
			str = ft_hd_dollar_check(str, pack);
		str = ft_strjoinmod(str, "\n");
		if (ft_strlen(str) == ft_strlen(limiter) && \
ft_strncmp(str, limiter, ft_strlen(str)) == 0)
		{
			free(str);
			free(limiter);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], str, ft_strlen(str));
		free(str);
	}
}

void	here_doc_single(t_exec_single *data, char *lim, t_shell *pack)
{
	pid_t	child;
	int		fd[2];

	pipe(fd);
	child = fork();
	if (child < 0)
		return ;
	if (child == 0)
	{
		child_doc(lim, fd, pack);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(child, NULL, 0);
	}
}

void	fake_child_doc(char *limiter)
{
	char	*str;

	limiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		str = readline("hd> ");
		str = ft_strjoinmod(str, "\n");
		if (ft_strlen(str) == ft_strlen(limiter) && \
ft_strncmp(str, limiter, ft_strlen(str)) == 0)
		{
			free(str);
			free(limiter);
			exit(EXIT_SUCCESS);
		}
		free(str);
	}
}

void	fake_here_doc(t_exec_single *data, char *lim)
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

void	fake_redoc(t_shell *data, t_exec_single *pack, int weight)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->token[0].scmd[i].type != 5 \
	&& i < data->token[0].nb_token)
		i++;
	while (j < pack->is_here_doc - weight)
	{
		if (data->token[0].scmd[i].type == TOKEN_INTPUT_HEREDOC_REDIRECTION \
		&& (i + 1) < data->token[0].nb_token && \
		data->token[0].scmd[i + 1].type == TOKEN_LIMITER)
			fake_here_doc(pack, ft_strdup(data->token[0].scmd[i + 1].value));
		else if (data->token[0].scmd[i].type == 5 \
		&& !((i + 1) < data->token[0].nb_token))
			data->error_ret = ft_syntax_error();
		i += 2;
		j++;
	}
}
