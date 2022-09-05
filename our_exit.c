/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilfried <wilfried@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:56:03 by wgaspar           #+#    #+#             */
/*   Updated: 2022/09/05 14:22:02 by wilfried         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*ft_exit_set_manage(t_manage_pipe *mpipe)
{
	free(mpipe->size_cmd);
	free(mpipe->pipecmd);
	return (NULL);
}

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

static int	wrong_argument_exit(char *str, t_shell *data)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	data->exit_switch = 1;
	data->exit_ret = 255;
	return (1);
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
		return (wrong_argument_exit(cmd[1], data));
	if (!cmd[1])
		data->exit_ret = 0;
	else if (cmd[1] && (ft_isonlynum(cmd[1]) == 0))
	{
		data->exit_ret = ft_atoi(cmd[1]);
	}
	data->exit_switch = 1;
	return (0);
}