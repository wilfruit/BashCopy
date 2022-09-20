/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_single.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:08:17 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/20 15:32:23 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static void	child_doc_eof(char *limiter, t_shell *pack)
{
	pack->error_ret = 0;
	maxi_free(pack);
	write(2, "\n", 1);
	exit(0);
}

void	child_doc(char *limiter, int *fd, t_shell *pack)
{
	char	*str;

	close(fd[0]);
	limiter = ft_strjoinmod(limiter, "\n");
	g_glob = 30;
	while (1)
	{
		str = readline("hd> ");
		if (ft_strncmp(limiter, str, ft_strlen(str)) != 0)
			str = ft_hd_dollar_check(str, pack);
		if (str == NULL)
			child_doc_eof(limiter, pack);
		str = ft_strjoinmod(str, "\n");
		if ((ft_strlen(str) == ft_strlen(limiter) && \
ft_strncmp(str, limiter, ft_strlen(str)) == 0))
		{
			free(str);
			maxi_free(pack);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], str, ft_strlen(str));
		free(str);
	}
}

static int	hd_s_parent(int status, pid_t child, t_shell *pack)
{
	g_glob = 30;
	sig_exit(pack, status, child, "messge");
	pack->error_ret = 1;
	return (1);
}

void	fake_child_doc(char *limiter)
{
	char	*str;

	limiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		str = readline("hd> ");
		if (str == NULL)
		{
			free(limiter);
			exit(0);
		}
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

int	here_doc_single(t_exec_single *data, char *lim, t_shell *pack)
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
		if (!no_command_found(pack, 0))
			spec_free(pack, data);
		child_doc(ft_strdup(lim), fd, pack);
		maxi_free(pack);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(child, &status, 0);
		if (status == 33280)
			return (hd_s_parent(status, child, pack));
		return (0);
	}
}
