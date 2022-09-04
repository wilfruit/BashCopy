/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <avaures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:55:20 by wgaspar           #+#    #+#             */
/*   Updated: 2022/08/30 20:50:21 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	size_tab(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

static int	is_option(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "-n", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	my_echo(char **cmd)
{
	int	endl;
	int	n;
	int	size;

	endl = is_option(cmd);
	size = size_tab(cmd);
	if (endl)
		n = 2;
	else
		n = 1;
	if (size > 1)
	{
		while (cmd[n])
		{
			ft_putstr_fd(cmd[n], 1);
			if (cmd[n + 1] && cmd[n][0])
				ft_putstr_fd(" ", 1);
			n++;
		}
	}
	if (endl == 0)
		write(1, "\n", 1);
	return (0);
}
