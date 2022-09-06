/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_five.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:03:00 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 17:03:01 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	redir_dup_single_builtin(t_shell *data, t_exec_single *pack)
{
	int		savein;
	int		saveout1;

	savein = 0;
	saveout1 = 0;
	if (pack->nb_redirin > 0)
	{
		savein = dup(0);
		close(0);
		dup2(pack->redirin, 0);
	}
	if (pack->nb_redirout > 0)
	{
		saveout1 = dup(1);
		close(1);
		dup2(pack->redirout, 1);
	}
	ft_exec_built_in(data, pack->cmdargs);
	clean_redir_single(pack, savein, saveout1);
}

void	mid_child(t_shell *data, t_exec_multi *pack, int n)
{
	mini_parse_multi(data, pack, n);
	close(pack->pipe_fd[n][0]);
	if (!pack->nb_redirin && !pack->is_here_doc)
	{
		dup2(pack->pipe_fd[n - 1][0], STDIN_FILENO);
		close(pack->pipe_fd[n - 1][0]);
	}
	if (get_last_redirin_m(data, pack, n) != 5)
	{
		dup2(pack->pipe_fd[n][1], STDOUT_FILENO);
		close(pack->pipe_fd[n][1]);
	}
	if (pack->nb_redirin || pack->nb_redirout || pack->is_here_doc)
		redir_dup_multi(data, pack, n);
	else
		ft_execve_multi(data, charize_env(data->our_env), pack);
}

void	ft_initsetman(t_manage_pipe *mpipe, char *line)
{
	mpipe->i = 0;
	mpipe->j = 0;
	mpipe->k = 0;
	mpipe->end = -1;
	mpipe->size = 0;
	mpipe->nb_cmd = size_cmd_tab(line);
}

static char	*ft_joined(char *s1, char *s2, char *sjoined)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[j])
	{
		sjoined[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		sjoined[i] = s2[j];
		i++;
		j++;
	}
	sjoined[i] = '\0';
	free (s1);
	return (sjoined);
}

char	*ft_strjoinmod(char *s1, char *s2)
{
	char	*sjoined;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	sjoined = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!sjoined)
		return (NULL);
	return (sjoined = ft_joined(s1, s2, sjoined));
}
