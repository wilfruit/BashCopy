/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:31:37 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/20 15:31:08 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	no_command_found(t_shell *data, int cell_nb)
{
	int	i;

	i = 0;
	while (i < data->token[cell_nb].nb_token \
	&& data->token[cell_nb].scmd[i].type != TOKEN_CMD)
		i++;
	if (i < data->token[cell_nb].nb_token \
	&& data->token[cell_nb].scmd[i].type == TOKEN_CMD)
		return (0);
	return (1);
}

int	ft_syntax_error(void)
{
	ft_putstr_fd("mshell: syntax error near unexpected token `newline'\n", 2);
	return (2);
}

void	cannot_execute(t_exec_single *data, char *cmd, char **env, t_shell *p)
{
	ft_putstr_fd("minishell: permission denied: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	if (env != NULL)
		ft_free_chr(env);
	if (!no_command_found(p, 0))
		spec_free(p, data);
	maxi_free(p);
	exit(126);
}

void	cmd_not_found(t_exec_single *data, char *av, char **env, t_shell *pack)
{	
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd(": command not found\n", 2);
	if (env != NULL)
		ft_free_chr(env);
	if (!no_command_found(pack, 0))
		spec_free(pack, data);
	maxi_free(pack);
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
