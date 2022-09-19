/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:31:59 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/16 12:17:04 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

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

void	sig_zigma(int sig)
{
	(void)sig;
	write (2, "\n", 1);
	g_glob = 30;
	exit(130);
}

void	sig_omega(int sig)
{
	exit(0);
}

void	wrap_execve(t_exec_single *data, t_shell *shpack, char **env)
{
	execve(data->cmddyn, data->cmdargs, env);
	cannot_execute(data, data->cmddyn, env, shpack);
}

void	ft_execve_one(t_shell *shpack, char **env, t_exec_single *data)
{
	int	i;

	i = -1;
	while (data->allpaths[++i] && data->cmdargs[0])
	{
		if (is_pathed(data->cmdargs[0]) == -1)
			data->cmddyn = ft_strjoin(data->allpaths[i], data->cmdstat);
		else
			data->cmddyn = data->cmdargs[0];
		if ((is_pathed(data->cmdargs[0]) == 0 \
		&& access(data->cmddyn, F_OK) != 0) \
		|| ft_strncmp(data->cmddyn, "/", ft_strlen(data->cmddyn)) == 0 || \
		ft_strncmp(data->cmddyn, "./", ft_strlen(data->cmddyn)) == 0)
			cmd_not_found(data, data->cmdargs[0], env, shpack);
		if (access(data->cmddyn, F_OK) == 0 && access(data->cmddyn, X_OK) == 0)
			wrap_execve(data, shpack, env);
		if (is_pathed(data->cmdargs[0]) == 0 && access(data->cmddyn, X_OK) != 0)
			cannot_execute(data, data->cmdargs[0], env, shpack);
		free(data->cmddyn);
	}
	cmd_not_found(data, data->cmdargs[0], env, shpack);
}
