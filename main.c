/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:59:10 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/17 14:39:48 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

volatile sig_atomic_t	g_glob = 0;

static void	create_minimum_data(t_shell *data, char **env)
{
	t_envi	*temp;
	t_envi	*cursor;

	cursor = ft_calloc(sizeof(t_envi), 1);
	cursor->str = ft_strdup("heyarnold\n");
	cursor->next = NULL;
	data->our_env = cursor;
	data->exports = cursor;
	cursor->str = ft_strdup("PWD=");
	temp = ft_calloc(sizeof(t_envi), 1);
	temp->str = ft_strdup("OLDPWD=");
	temp->next = NULL;
	cursor->next = temp;
	cursor = temp;
	temp = ft_calloc(sizeof(t_envi), 1);
	temp->str = ft_strdup("PATH=");
	temp->next = NULL;
	cursor->next = temp;
	cursor = temp;
	return ;
}

static void	shell_pack_init(t_shell *data, char **env)
{
	data->error_ret = 0;
	data->exit_switch = 0;
	data->exit_ret = 0;
	if (env[0])
	{
		download_env_one(data, env);
		download_env_two(data, env);
	}
	else
		create_minimum_data(data, env);
}

static int	sig_used(int error_ret, int i)
{
	if ((g_glob == 130 || g_glob == -130) && i == 0)
	{
		return (130);
	}
	else if ((g_glob == 130 || g_glob == -130) && i == 1)
	{
		g_glob = 0;
		return (130);
	}
	else if (g_glob == 30)
	{
		g_glob = 0;
		return (1);
	}
	else
		return (error_ret);
}

static void	ft_bash(t_shell *shell_pack, char *line)
{
	shell_pack->error_ret = sig_used(shell_pack->error_ret, 1);
	set_struct(&line, shell_pack->mpipe, &shell_pack->token);
	shell_pack->nb_cell = shell_pack->mpipe.nb_cmd;
	if (shell_pack->mpipe.size != 0)
		minishell_operator(shell_pack);
	clean_manage(&shell_pack->mpipe, &shell_pack->token);
}

int	main(int argc, char **argv, char **env)
{
	char			*line;
	char			*path;
	t_shell			shell_pack;

	shell_pack_init(&shell_pack, env);
	shell_pack.exit_switch = 0;
	line = NULL;
	while (shell_pack.exit_switch == 0)
	{
		control(&shell_pack);
		if (shell_pack.error_ret == 0)
			line = readline("\e[1;32mmshell> \e[0m");
		else if (shell_pack.error_ret != 0 \
		&& (g_glob == -130 || g_glob == 30 || g_glob == 130))
			line = readline("");
		else if (shell_pack.error_ret != 0 && g_glob != -130 && g_glob != 30)
			line = readline("\e[1;31mmshell> \e[0m");
		if (check_line(&line) == NULL)
			exit(0);
		if (all_pipe_cmd(&shell_pack.mpipe, line) != NULL)
			ft_bash(&shell_pack, line);
		free(line);
		shell_pack.error_ret = sig_used(shell_pack.error_ret, 0);
	}
	return (stop_minishell(&shell_pack));
}
