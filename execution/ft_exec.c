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

void	wrap_execve(t_exec_single *data, char *cmd, char **args, char **env)
{
	execve(cmd, args, env);
	cannot_execute(data, cmd, env);
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
			cmd_not_found(data, data->cmdargs[0], env);
		if (access(data->cmddyn, F_OK) == 0 && access(data->cmddyn, X_OK) == 0)
			wrap_execve(data, data->cmddyn, data->cmdargs, env);
		if (is_pathed(data->cmdargs[0]) == 0 && access(data->cmddyn, X_OK) != 0)
			cannot_execute(data, data->cmdargs[0], env);
		free(data->cmddyn);
	}
	free(data->cmdstat);
	cmd_not_found(data, data->cmdargs[0], env);
}
