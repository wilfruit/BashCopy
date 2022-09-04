/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <avaures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:55:43 by wgaspar           #+#    #+#             */
/*   Updated: 2022/08/30 20:51:09 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	my_env(t_envi *our_env, char **cmd)
{
	t_envi	*copy;

	if (cmd[0] && cmd[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	copy = our_env;
	while (copy)
	{
		ft_putendl_fd(copy->str, 1);
		copy = copy->next;
	}
	return (0);
}
