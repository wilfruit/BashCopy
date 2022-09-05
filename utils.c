/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:29:49 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/05 13:41:32 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	forced_prompt(int sig)
{
	glob = 130;
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\e[1;31mmshell> \e[0m", 1);
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
