/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:29:49 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/06 01:50:45 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	forced_prompt(int sig)
{
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\e[1;31mmshell> \e[0m", 1);
	rl_replace_line("", 0);
	if (g_glob != 130 && g_glob != -130)
		g_glob = 130;
}

void	forced_continue(int sig)
{
	(void) sig;
}

int	control(t_shell *data)
{
	signal(SIGINT, forced_prompt);
	signal(SIGQUIT, forced_continue);
}

void	free_token(t_manage_pipe utils, t_pipe **prompt)
{
	utils.i = -1;
	while (++utils.i < utils.nb_cmd)
	{
		utils.j = -1;
		while (++utils.j < (*prompt)[utils.i].nb_token)
		{
			free((*prompt)[utils.i].scmd[utils.j].value);
			(*prompt)[utils.i].scmd[utils.j].value = NULL;
		}
		free((*prompt)[utils.i].scmd);
	}
}

void	free_struct(t_manage_pipe utils, t_pipe **prompt)
{
	utils.i = -1;
	while (++utils.i < utils.nb_cmd)
	{
		free((*prompt)[utils.i].cmd);
		(*prompt)[utils.i].cmd = NULL;
	}
	free((*prompt));
}
