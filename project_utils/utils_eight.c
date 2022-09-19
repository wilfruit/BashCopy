/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_eight.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:24:38 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/19 14:47:19 by wgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	infile_not_allowed_m(t_exec_multi *pack, int n, t_shell *data, int i)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(data->token[n].scmd[i + 1].value, 2);
	ft_putendl_fd(" Permission denied", 2);
	data->error_ret = 1;
	return (1);
}

int	infile_not_real_m(t_exec_multi *pack, int n, t_shell *data, int i)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(data->token[n].scmd[i + 1].value, 2);
	ft_putendl_fd(" No such file or directory", 2);
	data->error_ret = 1;
	return (1);
}

int	outfile_not_allowed_m(t_exec_multi *pack, int n, t_shell *data, int i)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(data->token[n].scmd[i + 1].value, 2);
	ft_putendl_fd(" Permission denied", 2);
	data->error_ret = 1;
	return (1);
}

void	init_sig(void)
{
	int	i;

	i = -150000;
	while (i < 3000000)
		i++;
	return ;
}

int	stop_minishell(t_shell *shell_pack)
{
	ft_free_env(shell_pack->our_env);
	ft_free_env(shell_pack->exports);
	return (shell_pack->exit_ret);
}
