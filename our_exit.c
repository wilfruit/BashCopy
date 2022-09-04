/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <avaures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:56:03 by wgaspar           #+#    #+#             */
/*   Updated: 2022/08/30 20:52:07 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	ft_isonlynum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

int	my_exit(char **cmd, t_shell *data)
{
	ft_putstr_fd("exit\n", 2);
	if (cmd[0] && cmd[1] && cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->exit_ret = 1;
		data->exit_switch = 1;
		return (1);
	}
	if (cmd[1] && (ft_isonlynum(cmd[1]) == 1))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		data->exit_switch = 1;
		data->exit_ret = 255;
		return (1);
	}
	if (!cmd[1])
		data->exit_ret = 0;
	else if (cmd[1] && (ft_isonlynum(cmd[1]) == 0))
	{
		data->exit_ret = ft_atoi(cmd[1]);
	}
	data->exit_switch = 1;
	return (0);
}