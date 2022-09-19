/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:31:37 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/15 13:46:55 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_syntax_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
	return (258);
}

void	cannot_execute(t_exec_single *data, char *cmd, char **env)
{
	ft_putstr_fd("minishell: permission denied: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	if (env != NULL)
		ft_free_chr(env);
	free_exec_pack(data);
	exit(126);
}

void	cmd_not_found(t_exec_single *data, char *argv, char **env)
{	
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": command not found\n", 2);
	if (env != NULL)
		ft_free_chr(env);
	free_exec_pack(data);
	exit(127);
}

void	sig_exit(t_shell *data, int status, pid_t c1, char *cmd)
{
	data->error_ret = 0;
	data->error_ret = WTERMSIG(status);
	if (data->error_ret != 131)
		data->error_ret += 128;
	if (data->error_ret > 130)
	{
		ft_putstr_fd("[1]	", 2);
		ft_putnbr_fd(c1, 2);
		ft_putstr_fd(" abort (core dumped)	", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	if (data->error_ret == 130)
		g_glob = -130;
}
